// ------------------------------------------------------------	//
//																//
//																//
// ------------------------------------------------------------	//

#ifndef INGAMEMENU_HPP
# define INGAMEMENU_HPP

/*!
 * \file InGameMenu.hpp
 * \brief Menu affiché en cours de partie.
 * \author jblondea
 */

#include "Core/Core.hpp"
#include "Game/Game.hpp"
#include "Core/Component/Component.hpp"
#include "Core/Component/IStart.hpp"
#include "Core/Component/IEnable.hpp"
#include "Core/Component/IDisable.hpp"
#include "Core/Component/IStartUI.hpp"
#include "Core/Component/IUI.hpp"
#include "Game/SceneLoader.hpp"

namespace Game
{
	namespace Component
	{

		class InGameMenu : public BeerEngine::Component::Component, 
						public BeerEngine::Component::IStart,
						public BeerEngine::Component::IEnable,
						public BeerEngine::Component::IDisable,
						public BeerEngine::Component::IStartUI,
						public BeerEngine::Component::IUI

		{
		private:
			InGameMenu();
			InGameMenu(const InGameMenu &val);
			InGameMenu & operator=( InGameMenu const & rhs );

		public:
			UIThemeManager	*uiManager;
			Game::SceneLoader		sceneLoader;


			InGameMenu(BeerEngine::GameObject *gameObject);
			virtual ~InGameMenu( void );

			friend std::ostream & operator<<(std::ostream & o, InGameMenu const & i);

			virtual void start();
			virtual void enable();
			virtual void disable();
			virtual void startUI(struct nk_context *ctx, std::map<std::string, nk_font *> fonts);
			virtual void renderUI(struct nk_context *ctx);

			void setUI(struct nk_context *ctx);
			
			REGISTER_COMPONENT_HPP

		};

	};

};

#endif
