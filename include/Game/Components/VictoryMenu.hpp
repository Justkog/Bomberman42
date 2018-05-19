// ------------------------------------------------------------	//
//																//
//																//
// ------------------------------------------------------------	//

#ifndef VICTORYMENU_HPP
# define VICTORYMENU_HPP

/*!
 * \file VictoryMenu.hpp
 * \brief Affichage du menu de victoire.
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
		class VictoryMenu : public BeerEngine::Component::Component, 
						public BeerEngine::Component::IStart, 
						public BeerEngine::Component::IStartUI, 
						public BeerEngine::Component::IUI,
						public BeerEngine::Component::IEnable
		{
		public:
			UIThemeManager	*uiManager;
			nk_style_item	backgroundImage;
			nk_style_item	titleImage;
			Game::SceneLoader		sceneLoader;

			// VictoryMenu( void );
			// VictoryMenu( VictoryMenu const & src );
			VictoryMenu(BeerEngine::GameObject *gameObject);

			virtual ~VictoryMenu( void );

			VictoryMenu & operator=( VictoryMenu const & rhs );
			friend std::ostream & operator<<(std::ostream & o, VictoryMenu const & i);

			virtual void start();
			virtual void startUI(struct nk_context *ctx, std::map<std::string, nk_font *> fonts);
			virtual void renderUI(struct nk_context *ctx);
			virtual void enable();

			REGISTER_COMPONENT_HPP
	
		};

	};

};

#endif
