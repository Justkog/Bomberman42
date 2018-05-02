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


		class RaysRenderer : public BeerEngine::Component::MeshRenderer,
								public BeerEngine::Component::IStart
		{
		public:

			// RaysRenderer( void );
			// RaysRenderer( RaysRenderer const & src );
			RaysRenderer(BeerEngine::GameObject *gameObject);

			virtual ~RaysRenderer( void );

			RaysRenderer & operator=( RaysRenderer const & rhs );
			friend std::ostream & operator<<(std::ostream & o, RaysRenderer const & i);

			virtual void start();
			virtual void renderUpdate(void);

			void addRay(Physics::Ray ray);
			void RebuildMesh();
	
			std::vector<Physics::Ray> rays;
			int old_size;
		};

	};

};

#endif
