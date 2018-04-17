#include "Core/Component/MeshRenderer.hpp"
#include "Core/GameObject.hpp"

namespace BeerEngine
{
	namespace Component
	{
		MeshRenderer::MeshRenderer(GameObject *gameObject) :
			Component(gameObject),
			_mesh(nullptr),
			_material(nullptr)
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
				if (_material != nullptr)
					_material->bind(_mat);
				_mesh->render();
			}
		}
	}
}