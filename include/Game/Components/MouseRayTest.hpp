// ------------------------------------------------------------	//
//																//
//																//
// ------------------------------------------------------------	//

#ifndef MOUSERAYTEST_HPP
# define MOUSERAYTEST_HPP

#include "Core/Core.hpp"
#include "Core/Component/Component.hpp"
#include "Core/Component/IStart.hpp"
#include "Core/Component/IUpdate.hpp"
#include "Core/Component/IRender.hpp"

namespace Game
{
	namespace Component
	{
		struct Ray
		{
			glm::vec3 origin;
			glm::vec3 direction;
		};

		class MouseRayTest : public BeerEngine::Component::Component, 
								public BeerEngine::Component::IUpdate, 
								public BeerEngine::Component::IStart,
								public BeerEngine::Component::IRender
		{
		public:

			// MouseRayTest( void );
			// MouseRayTest( MouseRayTest const & src );
			MouseRayTest(BeerEngine::GameObject *gameObject);

			virtual ~MouseRayTest( void );

			MouseRayTest & operator=( MouseRayTest const & rhs );
			friend std::ostream & operator<<(std::ostream & o, MouseRayTest const & i);

			virtual void start();
			virtual void update();
			virtual void fixedUpdate();
			virtual void renderUpdate(void);
			virtual void render(void);

			Ray MouseToWorldRay();
			Ray ScreenToWorldRay(glm::vec2 screenPosition);
			void RebuildMesh();
	
			std::vector<Ray> rays;

			bool clicking;
			int old_size;
			BeerEngine::Component::MeshRenderer *linesRenderer;
		};

	};

};

#endif
