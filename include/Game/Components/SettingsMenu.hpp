// ------------------------------------------------------------	//
//																//
//																//
// ------------------------------------------------------------	//

#ifndef SETTINGSMENU_HPP
# define SETTINGSMENU_HPP

#include "Core/Core.hpp"
#include "Core/Component/Component.hpp"
#include "Core/Component/IStart.hpp"
#include "Core/Component/IUpdate.hpp"

namespace Game
{
	namespace Component
	{
		class SettingsMenu : public BeerEngine::Component::Component, public BeerEngine::Component::IUpdate, public BeerEngine::Component::IStart
		{
		public:

			// SettingsMenu( void );
			// SettingsMenu( SettingsMenu const & src );
			SettingsMenu(BeerEngine::GameObject *gameObject);

			virtual ~SettingsMenu( void );

			SettingsMenu & operator=( SettingsMenu const & rhs );
			friend std::ostream & operator<<(std::ostream & o, SettingsMenu const & i);

			virtual void start();
			virtual void update();
			virtual void fixedUpdate();
	
		};

	};

};

#endif
