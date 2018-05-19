// ------------------------------------------------------------	//
//																//
//																//
// ------------------------------------------------------------	//

#ifndef MOUSERAYTEST_HPP
# define MOUSERAYTEST_HPP

/*!
 * \file MouseRayTest.hpp
 * \brief Component d'exemple pour l'utilisation du mouseToWorldRay et du RaysRenderer.
 * \author jblondea
 */

#include "Core/Core.hpp"
#include "Core/Component/Component.hpp"
#include "Core/Component/IStart.hpp"
#include "Core/Component/IUpdate.hpp"
#include "Core/Component/IRender.hpp"

namespace Game
{
	namespace Component
	{
		class MouseRayTest : public BeerEngine::Component::Component, 
								public BeerEngine::Component::IUpdate, 
								public BeerEngine::Component::IStart
		{
		public:
			MouseRayTest();
			MouseRayTest(const MouseRayTest &val);
			MouseRayTest(BeerEngine::GameObject *gameObject);

			virtual ~MouseRayTest( void );

			MouseRayTest & operator=( MouseRayTest const & rhs );
			friend std::ostream & operator<<(std::ostream & o, MouseRayTest const & i);

			virtual void start();
			virtual void update();
			virtual void fixedUpdate();

			bool clicking;
			BeerEngine::Component::RaysRenderer *linesRenderer;

			REGISTER_COMPONENT_HPP
		};

	};

};

#endif
