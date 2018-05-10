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

		void    		MeshRenderer::render(void)
		{
			if (_mesh != nullptr)
			{
				std::vector<Graphics::ALight*> lights = SceneManager::GetCurrent()->getLights();
				Graphics::AMaterial *mat = Graphics::Graphics::defaultMaterial;
				if (_material != nullptr)
					mat = _material;
				mat->bind(_mat);
				_mesh->render(renderMode, Graphics::Graphics::defaultLight);
				Graphics::Graphics::EnableForwardBlend();
				for (Graphics::ALight *light : lights)
				{
					mat->bind(_mat);
					_mesh->render(renderMode, light);
				}
				Graphics::Graphics::DisableForwardBlend();
			}
		}

		nlohmann::json	MeshRenderer::serialize()
		{
			return nlohmann::json {
				{"componentClass", type},
				{"mesh", _mesh},
				{"material", _material},
				{"pivot", _mat},
			};
		}

		void MeshRenderer::deserialize(const nlohmann::json & j)
		{
			// std::cout << this->_sourceFile << "\n";
			// this->_sourceFile = j.at("sourceFile");
			// if (this->_sourceFile != "")
			// 	this->setMesh(this->_sourceFile);
			this->setMesh(Graphics::Mesh::Deserialize(j.at("mesh")));
			this->setMaterial(Graphics::AMaterial::Deserialize(j.at("material")));
			this->_mat = j.at("pivot");
		}

		REGISTER_COMPONENT_CPP(MeshRenderer)
	}
}
