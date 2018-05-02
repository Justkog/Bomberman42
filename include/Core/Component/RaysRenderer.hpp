// ------------------------------------------------------------	//
//																//
//																//
// ------------------------------------------------------------	//

#ifndef RAYS_RENDERER_HPP
# define RAYS_RENDERER_HPP

#include "Core/Core.hpp"
#include "Core/Component/MeshRenderer.hpp"
#include "Core/Component/IStart.hpp"
#include "Core/Component/IUpdate.hpp"
#include "Core/Component/IRender.hpp"

namespace BeerEngine
{
	namespace Component
	{
		struct Ray
		{
			glm::vec3 origin;
			glm::vec3 direction;
		};

		class RaysRenderer : public BeerEngine::Component::MeshRenderer,
								// public BeerEngine::Component::IUpdate, 
								public BeerEngine::Component::IStart
								// public BeerEngine::Component::IRender
		{
		public:

			// RaysRenderer( void );
			// RaysRenderer( RaysRenderer const & src );
			RaysRenderer(BeerEngine::GameObject *gameObject);

			virtual ~RaysRenderer( void );

			RaysRenderer & operator=( RaysRenderer const & rhs );
			friend std::ostream & operator<<(std::ostream & o, RaysRenderer const & i);

			virtual void start();
			// virtual void update();
			// virtual void fixedUpdate();
			virtual void renderUpdate(void);

			void addRay(Ray ray);
			Ray MouseToWorldRay();
			Ray ScreenToWorldRay(glm::vec2 screenPosition);
			void RebuildMesh();
	
			std::vector<Ray> rays;

			bool clicking;
			int old_size;
			// BeerEngine::Component::MeshRenderer *linesRenderer;
		};

	};

};

#endif
