#include "Core/AScene.hpp"
#include "Core/Graphics/Particles.hpp"

namespace BeerEngine
{
    int     AScene::uniqueID = 0;

    AScene::AScene(void)
    {
        
    }

    AScene::~AScene(void)
    {
        std::map<int, GameObject *>::iterator it;
        for (it = _gameObjects.begin(); it != _gameObjects.end(); ++it)
        {
            delete (it->second);
        }
        _gameObjects.clear();
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
        std::map<int, GameObject *>::iterator it;
        for (it = _gameObjects.begin(); it != _gameObjects.end(); ++it)
        {
            (it->second)->start();
            (it->second)->componentStart();
        }
    }

    void    AScene::fixedUpdate(void)
    {
        std::map<int, GameObject *>::iterator it;
        for (it = _gameObjects.begin(); it != _gameObjects.end(); ++it)
        {
            (it->second)->fixedUpdate();
            (it->second)->componentFixedUpdate();
        }
    }

    void    AScene::update(void)
    {
        std::map<int, GameObject *>::iterator it;
        for (it = _gameObjects.begin(); it != _gameObjects.end(); ++it)
        {
            (it->second)->update();
            (it->second)->componentUpdate();
        }
    }

    void    AScene::renderUpdate(void)
    {
        std::map<int, GameObject *>::iterator it;
        for (it = _gameObjects.begin(); it != _gameObjects.end(); ++it)
        {
            (it->second)->renderUpdate();
            (it->second)->componentRenderUpdate();
        }
    }

    void    AScene::render(void)
    {
        std::map<int, GameObject *>::iterator it;
        for (it = _gameObjects.begin(); it != _gameObjects.end(); ++it)
        {
            (it->second)->render();
            (it->second)->componentRender();
        }
    }

    void    AScene::physicUpdate(void)
    {
        std::map<int, GameObject *>::iterator it;
        for (it = _gameObjects.begin(); it != _gameObjects.end(); ++it)
        {
            (it->second)->componentPhysicUpdate();
        }
    }

    void    AScene::destroy(GameObject *go)
    {
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
            {
                delete it->second;
                _gameObjects.erase(it);
            }
		}
        _toDestroy.clear();
    }
}