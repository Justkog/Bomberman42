#ifndef BE_CORE_COMPONENT_MESHRENDERER_HPP
#define BE_CORE_COMPONENT_MESHRENDERER_HPP 1

#include "Component.hpp"
#include "IRender.hpp"
#include "../Graphics/Mesh.hpp"
#include "../Graphics/AMaterial.hpp"

namespace BeerEngine
{
	namespace Component
	{
		class MeshRenderer : public Component, public IRender
		{
		protected:
			Graphics::Mesh		*_mesh;
			Graphics::AMaterial	*_material;
			glm::mat4			_mat;

		public:
			MeshRenderer(GameObject *gameObject);
			Graphics::Mesh	*getMesh(void);
			MeshRenderer	&setMesh(Graphics::Mesh *mesh);
			MeshRenderer	&setMesh(std::string inputfile);	
			Graphics::AMaterial	*getMaterial(void);
			MeshRenderer	&setMaterial(Graphics::AMaterial *material);
			virtual void    renderUpdate(void);
			virtual void    render(void);

		};
	}
}

#endif
