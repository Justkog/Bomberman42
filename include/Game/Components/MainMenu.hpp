// ------------------------------------------------------------	//
//																//
//																//
// ------------------------------------------------------------	//

#ifndef MAINMENU_HPP
# define MAINMENU_HPP

#include "Core/Core.hpp"
#include "Game/Game.hpp"
#include "Core/Component/Component.hpp"
#include "Core/Component/IStart.hpp"
#include "Core/Component/IStartUI.hpp"
#include "Core/Component/IUI.hpp"

namespace Game
{
	namespace Component
	{
		class MainMenu : public BeerEngine::Component::Component, 
						public BeerEngine::Component::IStart,
						public BeerEngine::Component::IStartUI,
						public BeerEngine::Component::IUI

		{
		public:
			SettingsMenu	*settingsMenu;
			VersusMenu	*versusMenu;
			UIThemeManager	*uiManager;

			nk_style_window mWindow;

			// MainMenu( void );
			// MainMenu( MainMenu const & src );
			MainMenu(BeerEngine::GameObject *gameObject);

			virtual ~MainMenu( void );

			MainMenu & operator=( MainMenu const & rhs );
			friend std::ostream & operator<<(std::ostream & o, MainMenu const & i);

			virtual void start();
			virtual void startUI(struct nk_context *ctx, std::map<std::string, nk_font *> fonts);
			virtual void renderUI(struct nk_context *ctx);

			void setUI(struct nk_context *ctx);

			virtual nlohmann::json	serialize();
			virtual void deserialize(const nlohmann::json & j);

			REGISTER_COMPONENT_HPP
		};

	};

};

#endif
