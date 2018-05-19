// ------------------------------------------------------------	//
//																//
//																//
// ------------------------------------------------------------	//

#ifndef GAMEOVERMENU_HPP
# define GAMEOVERMENU_HPP

/*!
 * \file GameOverMenu.hpp
 * \brief Menu affiché en cas de Game Over.
 * \author jblondea
 */

#include "Core/Core.hpp"
#include "Game/Game.hpp"
#include "Core/Component/Component.hpp"
#include "Core/Component/IStart.hpp"
#include "Core/Component/IStartUI.hpp"
#include "Core/Component/IUI.hpp"
#include "Core/Component/IEnable.hpp"
#include "Game/SceneLoader.hpp"

namespace Game
{
	namespace Component
	{
		class GameOverMenu : public BeerEngine::Component::Component, 
						public BeerEngine::Component::IStart, 
						public BeerEngine::Component::IStartUI, 
						public BeerEngine::Component::IUI,
						public BeerEngine::Component::IEnable
		{
		private:
			GameOverMenu();
			GameOverMenu(const GameOverMenu &val);
			GameOverMenu & operator=( GameOverMenu const & rhs );

		public:
			UIThemeManager	*uiManager;
			nk_style_item	backgroundImage;
			nk_style_item	youLoseImage;
			Game::SceneLoader		sceneLoader;

			GameOverMenu(BeerEngine::GameObject *gameObject);
			virtual ~GameOverMenu( void );

			friend std::ostream & operator<<(std::ostream & o, GameOverMenu const & i);

			virtual void start();
			virtual void startUI(struct nk_context *ctx, std::map<std::string, nk_font *> fonts);
			virtual void renderUI(struct nk_context *ctx);
			virtual void enable();
			
			REGISTER_COMPONENT_HPP
	
		};

	};

};

#endif
