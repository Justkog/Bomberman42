#ifndef BE_CORE_COMPONENT_MESHRENDERER_HPP
#define BE_CORE_COMPONENT_MESHRENDERER_HPP 1
/*!
 * \file MeshRenderer.hpp
 * \brief Component permettent d'ajouter un rendu au component
 * \author mgallo, mploux, jblondea
 */
#include "Core/Core.hpp"
#include "Component.hpp"
#include "IRenderForward.hpp"
#include "IRenderShadow.hpp"
#include "Core/Graphics/Lights/ALight.hpp"

/*! \namespace BeerEngine
 * espace de nommage regroupant les fonctionnalité du moteur
 */
namespace BeerEngine
{
	/*! \namespace Component
	* espace de nommage regroupant les fonctionnalité des Component du moteur
	*/
	namespace Component
	{
		/*! \class MeshRenderer
		* \brief Component d'ajouter et de rendre a l'ecran un mesh
		*/
		class MeshRenderer : public Component, public IRenderForward, public IRenderShadow
		{
		protected:
			Graphics::Mesh		*_mesh;
			Graphics::AMaterial	*_material;
			glm::mat4			_mat;
			std::string			_sourceFile;
		
			MeshRenderer();
			MeshRenderer(const MeshRenderer &val);
			MeshRenderer &operator=(const MeshRenderer &val);

		public:
			virtual ~MeshRenderer();

			MeshRenderer(GameObject *gameObject);
			Graphics::Mesh	*getMesh(void);
			MeshRenderer	&setMesh(Graphics::Mesh *mesh);
			MeshRenderer	&setMesh(std::string inputfile);	
			Graphics::AMaterial	*getMaterial(void);
			MeshRenderer	&setMaterial(Graphics::AMaterial *material);

			virtual void    renderUpdate(void);
			virtual void    render(BeerEngine::Graphics::ALight &light);
			virtual void    renderShadowUpdate(void);
			virtual void    renderShadow(void);
			virtual bool	castShadows(void);
			virtual bool	receiveShadows(void);

			GLenum 			renderMode;

			REGISTER_COMPONENT_HPP
		};
	}
}

#endif
