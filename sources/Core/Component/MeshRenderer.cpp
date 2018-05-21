#include "Core/Component/MeshRenderer.hpp"
#include "Core/Graphics/MeshBuilder.hpp"
#include "Core/Graphics/Graphics.hpp"
#include "Core/SceneManager.hpp"
#include "Core/GameObject.hpp"
#include "Core/Graphics/AMaterial.hpp"
#include "Core/Json/Json.hpp"

namespace BeerEngine
{
	namespace Component
	{
		MeshRenderer::MeshRenderer(GameObject *gameObject) :
			Component(gameObject),
			_mesh(nullptr),
			_material(nullptr),
			renderMode(GL_TRIANGLES)
		{}

		MeshRenderer::MeshRenderer() :
			Component()
		{}

		MeshRenderer::MeshRenderer(const MeshRenderer &val)
		{
			*this = val;
		}
		
		MeshRenderer &MeshRenderer::operator=(const MeshRenderer &val)
		{
			if (this != &val)
			{
				if (_mesh)
					delete _mesh;
				_mesh = val._mesh;
				_material = val._material;
				_mat = val._mat;
				_sourceFile = val._sourceFile;
				renderMode = val.renderMode;
			}
			return (*this);
		}

		MeshRenderer::~MeshRenderer()
		{
			if (_material != nullptr)
				delete _material;
			if (_mesh != nullptr)
				Graphics::Graphics::deleteMesh(_mesh);
		}

		Graphics::Mesh	*MeshRenderer::getMesh(void)
		{
			return (_mesh);
		}

		MeshRenderer		&MeshRenderer::setMesh(Graphics::Mesh *mesh)
		{
			_mesh = mesh;
			return (*this);
		}

		MeshRenderer		&MeshRenderer::setMesh(std::string inputfile)
		{
			return setMesh(BeerEngine::Graphics::Graphics::OBJLoader(inputfile));
		}

		Graphics::AMaterial	*MeshRenderer::getMaterial(void)
		{
			return (_material);
		}

		MeshRenderer	&MeshRenderer::setMaterial(Graphics::AMaterial *material)
		{
			_material = material;
			return (*this);
		}

		void    		MeshRenderer::renderUpdate(void)
		{
			_mat = _gameObject->transform.getMat4();
		}

		void    		MeshRenderer::render(Graphics::ALight &light)
		{
			if (_mesh != nullptr)
			{
				if (_material != nullptr)
					_material->bind(_mat, light);
				light.getShader().uniform1i("hasBones", 0);
				_mesh->render(renderMode);
			}
		}

		void    MeshRenderer::renderShadowUpdate(void)
		{

		}

		void    MeshRenderer::renderShadow(void)
		{
			if (_mesh != nullptr)
			{
				Graphics::Graphics::shadowRenderShader->uniformMat("model", _mat);
				Graphics::Graphics::shadowRenderShader->uniform1i("hasBones", 0);
				_mesh->render(renderMode);
			}
		}

		bool	MeshRenderer::castShadows(void)
		{
			return true;
		}

		bool	MeshRenderer::receiveShadows(void)
		{
			return true;
		}

		nlohmann::json	MeshRenderer::serialize()
		{
			auto j = Component::serialize();
			j.merge_patch({
				{"componentClass", type},
				{"mesh", _mesh},
				{"material", _material},
				{"pivot", _mat},
			});
			return j;
		}

		void MeshRenderer::deserialize(const nlohmann::json & j, BeerEngine::JsonLoader & loader)
		{
			// std::cout << this->_sourceFile << "\n";
			// this->_sourceFile = j.at("sourceFile");
			// if (this->_sourceFile != "")
			// 	this->setMesh(this->_sourceFile);
			this->Component::deserialize(j, loader);
			if (j.find("mesh") != j.end())
				this->setMesh(Graphics::Mesh::Deserialize(j.at("mesh"), loader));
			if (j.find("material") != j.end())
				this->setMaterial(Graphics::AMaterial::Deserialize(j.at("material"), loader));
			this->_mat = j.at("pivot");
		}

		REGISTER_COMPONENT_CPP(MeshRenderer)
	}
}
