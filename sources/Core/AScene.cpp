#include "Core/AScene.hpp"
#include "Core/Core.hpp"
#include "Core/GameObject.hpp"
#include "Core/Window.hpp"
#include "Core/Camera.hpp"
#include "Core/Component/Component.hpp"
#include "Core/Component/MeshRenderer.hpp"
#include "Core/Graphics/Mesh.hpp"
#include "Core/Graphics/MeshBuilder.hpp"
#include "Core/Graphics/ShaderProgram.hpp"
#include "Core/Graphics/Graphics.hpp"
#include "Core/Graphics/AMaterial.hpp"
#include "Core/Graphics/Lights/ALight.hpp"
#include "Core/Graphics/Lights/DirectionalLight.hpp"
#include "Core/IO/FileUtils.hpp"
#include "Core/Json/Json.hpp"

namespace BeerEngine
{
    int     AScene::uniqueID = 0;

    AScene::AScene(void)
        : _skyboxCubemap(nullptr)
    {}

    AScene::AScene(const AScene &val)
    {
        *this = val;
    }

    AScene &AScene::operator=(const AScene &val)
    {
        if (this != &val)
        {
            AScene::~AScene();
            for (const std::pair<int, GameObject *> &p : val._gameObjects)
                _gameObjects[p.first] = p.second;
            for (const std::pair<int, Graphics::ALight *> &p : val._lights)
                _lights[p.first] = p.second;
            for (std::size_t i = 0; i < val._toDestroy.size(); i++)
                _toDestroy.push_back(val._toDestroy[i]);
            for (std::size_t i = 0; i < val._toStart.size(); i++)
                _toStart.push_back(val._toStart[i]);
            for (std::size_t i = 0; i < val._toStartUI.size(); i++)
                _toStartUI.push_back(val._toStartUI[i]);
            _skyboxCubemap = val._skyboxCubemap;
        }
        return (*this);
    }

    AScene::~AScene(void)
    {
        std::map<int, GameObject *>::iterator it;
        std::map<int, Graphics::ALight *>::iterator it2;
        for (it = _gameObjects.begin(); it != _gameObjects.end(); ++it)
        {
            (it->second)->componentOnDestroy();
        }
        for (it = _gameObjects.begin(); it != _gameObjects.end(); ++it)
        {
            delete (it->second);
        }
        for (it2 = _lights.begin(); it2 != _lights.end(); ++it2)
        {
            delete (it2->second);
        }
        _gameObjects.clear();
        _lights.clear();
        if (_skyboxCubemap)
            delete _skyboxCubemap;
    }

    std::vector<GameObject *> AScene::getGameObjects()
    {
        std::vector<GameObject *> res;

        // populate map somehow
        for(auto it = _gameObjects.begin(); it != _gameObjects.end(); ++it) {
            res.push_back( it->second );
        }
        return (res);
    }

    std::vector<Graphics::ALight *> AScene::getLights()
    {
        std::vector<Graphics::ALight *> res;

        // populate map somehow
        for(auto it = _lights.begin(); it != _lights.end(); ++it) {
            res.push_back( it->second );
        }
        return (res);
    }

    void AScene::debugTest(void)
    {
        std::cout << "GameObject List Size : " << _gameObjects.size() << std::endl;
    }

	GameObject *AScene::find(std::string name)
	{
		for(auto it = _gameObjects.begin(); it != _gameObjects.end(); ++it) {
			if (it->second->name == name)
				return it->second;
        }
		return NULL;
	}

     void    AScene::mutexLock(bool lock)
     {
        if (lock)
            updateMutex.lock();
        else
            updateMutex.unlock();
     }

    void    AScene::start(void)
    {
		// std::cout << "DEBUG: AScene::start" << std::endl;
        for (GameObject *go : _toStart)
        {
            go->start();
        }
        _toStart.clear();
        std::map<int, GameObject *>::iterator it;
        for (it = _gameObjects.begin(); it != _gameObjects.end(); ++it)
        {
            (it->second)->componentStart();
        }
		for (it = _gameObjects.begin(); it != _gameObjects.end(); ++it)
        {
            (it->second)->componentDisable();
            (it->second)->componentEnable();
        }
    }

    void    AScene::fixedUpdate(void)
    {
        // std::cout << "DEBUG: AScene::fixedUpdate" << std::endl;
        std::map<int, GameObject *>::iterator it;
        for (it = _gameObjects.begin(); it != _gameObjects.end(); ++it)
        {
            (it->second)->fixedUpdate();
            (it->second)->componentFixedUpdate();
        }
    }

    void    AScene::update(void)
    {
        // std::cout << "DEBUG: AScene::update" << std::endl;
        std::map<int, GameObject *>::iterator it;
        for (it = _gameObjects.begin(); it != _gameObjects.end(); ++it)
        {
            (it->second)->update();
            (it->second)->componentUpdate();
        }
    }

    void    AScene::renderUpdate(void)
    {
        // std::cout << "DEBUG: AScene::renderUpdate" << std::endl;
        std::map<int, GameObject *>::iterator it;
        for (it = _gameObjects.begin(); it != _gameObjects.end(); ++it)
        {
            (it->second)->renderUpdate();
            (it->second)->componentRenderUpdate();
        }
        if (_skyboxCubemap)
            _skyboxCubemap->renderUpdate();
    }

    void    AScene::render(void)
    {
        // std::cout << "DEBUG: AScene::render" << std::endl;
        if (_skyboxCubemap)
            _skyboxCubemap->render();
        renderShadows();
        renderForward();
        std::map<int, GameObject *>::iterator it;
        for (it = _gameObjects.begin(); it != _gameObjects.end(); ++it)
        {
            (it->second)->render();
            (it->second)->componentRender();
        }
        for (it = _gameObjects.begin(); it != _gameObjects.end(); ++it)
        {
            (it->second)->componentRenderAlpha();
        }
    }

    void    AScene::renderForward(void)
    {
        std::map<int, GameObject *>::iterator it;
        std::map<int, Graphics::ALight *>::iterator it2;

        Graphics::Graphics::defaultLight->bind();
        for (it2 = _lights.begin(); it2 != _lights.end(); ++it2)
        {
            it2->second->bind();
        }
        for (it = _gameObjects.begin(); it != _gameObjects.end(); ++it)
        {
            (it->second)->componentRenderForward(*Graphics::Graphics::defaultLight);
        } 
    }

    void    AScene::renderShadows(void)
    {
        std::map<int, Graphics::ALight *>::iterator it2;
        for (it2 = _lights.begin(); it2 != _lights.end(); ++it2)
        {
            Graphics::DirectionalLight *light;
            if ((light = dynamic_cast<Graphics::DirectionalLight *>(it2->second)) == nullptr)
                continue;
            light->bindShadowMap();
            
            glEnable(GL_DEPTH_TEST);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            Graphics::Graphics::shadowRenderShader->bind();
            glm::mat4 proj = light->getLightProjection();
            Graphics::Graphics::shadowRenderShader->uniformMat("projection", proj);
            glm::mat4 lookat = glm::lookAt(glm::vec3(0, 0, 0), light->getDirection() * -1, glm::vec3(0, 1, 0));
            Graphics::Graphics::shadowRenderShader->uniformMat("view", lookat);
            std::map<int, GameObject *>::iterator it;
            for (it = _gameObjects.begin(); it != _gameObjects.end(); ++it)
            {
                (it->second)->componentRenderShadows();
            }
            Graphics::Graphics::shadowRenderShader->unbind();

            light->unbindShadowMap();

            // light->drawShadowMap();
        }
    }

	void    AScene::startUI(struct nk_context *ctx, std::map<std::string, nk_font *> fonts)
    {
        for (GameObject *go : _toStartUI)
        {
            go->startUI(ctx, fonts);
        }
        _toStartUI.clear();
        std::map<int, GameObject *>::iterator it;
        for (it = _gameObjects.begin(); it != _gameObjects.end(); ++it)
        {
            (it->second)->componentStartUI(ctx, fonts);
        }
    }

    void    AScene::renderUI(struct nk_context *ctx)
    {
        // std::cout << "DEBUG: AScene::renderUI" << std::endl;
        std::map<int, GameObject *>::iterator it;
        for (it = _gameObjects.begin(); it != _gameObjects.end(); ++it)
        {
            (it->second)->renderUI(ctx);
            (it->second)->componentRenderUI(ctx);
        }
    }

    void    AScene::physicUpdate(void)
    {
        // std::cout << "DEBUG: AScene::physicUpdate" << std::endl;
        std::map<int, GameObject *>::iterator it;
        for (it = _gameObjects.begin(); it != _gameObjects.end(); ++it)
        {
            (it->second)->componentPhysicUpdate();
        }
    }

    void AScene::setSkybox(Graphics::Cubemap *cubemap)
    {
        _skyboxCubemap = cubemap;
    }

    void    AScene::save(std::string filePath) {
        (void) filePath;
        nlohmann::json j = dynamic_cast<JsonSerializable *>(this);
        std::string content = j.dump(4);
        // BeerEngine::IO::FileUtils::WriteFile(filePath, content);
        // std::cout << content << std::endl;
    }

    void    AScene::load(std::string filePath) {
        std::string content = BeerEngine::IO::FileUtils::LoadFile(filePath);
        std::cout << "deserializing " << filePath << "\n";
        auto j = nlohmann::json::parse(content);
		BeerEngine::JsonLoader loader;
        this->deserialize(j, loader);
		loader.executeCallBacks();
    }

    nlohmann::json	AScene::serialize()
	{
		return nlohmann::json {
            {"gameObjects", JsonSerializable::toSerializables<BeerEngine::GameObject>(this->getGameObjects())},
        };
	}

    void AScene::deserialize(const nlohmann::json & j, BeerEngine::JsonLoader & loader)
    {
		std::cout << "deserializing scene" << "\n";
		auto gameObjects = j.at("gameObjects");
		for (nlohmann::json::iterator it = gameObjects.begin(); it != gameObjects.end(); ++it) {
			auto goJson = it.value();
			GameObject::Deserialize(goJson, loader, *this);
		}
	}

    void    AScene::destroy(GameObject *go)
    {
        std::map<int, GameObject *>::iterator it;
        for (it = _gameObjects.begin(); it != _gameObjects.end(); ++it)
        {
            if ((it->second)->transform.parent == &(go->transform))
                destroy((it->second));
        }
        if(std::find(_toDestroy.begin(), _toDestroy.end(), go) == _toDestroy.end())
        {
            _toDestroy.push_back(go);
        }
    }

    void    AScene::destroyGameObjects(void)
    {
        for (GameObject *go : _toDestroy)
		{
            std::map<int, GameObject *>::iterator it;
			if ((it = _gameObjects.find(go->_uniqueID)) != _gameObjects.end())
                (it->second)->componentOnDestroy();
		}
        for (GameObject *go : _toDestroy)
		{
            std::map<int, GameObject *>::iterator it;
			if ((it = _gameObjects.find(go->_uniqueID)) != _gameObjects.end())
            {
                delete it->second;
                _gameObjects.erase(it);
            }
		}
        _toDestroy.clear();
        std::map<int, GameObject *>::iterator it;
        for (it = _gameObjects.begin(); it != _gameObjects.end(); ++it)
        {
            (it->second)->destroyComponent();
        }
    }
}