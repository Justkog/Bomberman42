// ------------------------------------------------------------	//
//																//
//																//
// ------------------------------------------------------------	//

#ifndef ADVENTUREMENU_HPP
# define ADVENTUREMENU_HPP

#include "Core/Core.hpp"
#include "Game/Game.hpp"
#include "Core/Component/Component.hpp"
#include "Core/Component/IStart.hpp"
#include "Core/Component/IStartUI.hpp"
#include "Core/Component/IUI.hpp"
#include "Game/SceneLoader.hpp"

namespace Game
{
	namespace Component
	{
		class AdventureMenu : public BeerEngine::Component::Component, 
						public BeerEngine::Component::IStart, 
						public BeerEngine::Component::IStartUI, 
						public BeerEngine::Component::IUI
		{
		public:
			UIThemeManager			*uiManager;
			MainMenu				*mainMenu;
			AdventureContinueMenu	*continueMenu;
			GameProgression			*gameProgression;
			Game::SceneLoader		sceneLoader;


			// AdventureMenu( void );
			// AdventureMenu( AdventureMenu const & src );
			AdventureMenu(BeerEngine::GameObject *gameObject);

			virtual ~AdventureMenu( void );

			AdventureMenu & operator=( AdventureMenu const & rhs );
			friend std::ostream & operator<<(std::ostream & o, AdventureMenu const & i);

			virtual void start();
			virtual void startUI(struct nk_context *ctx, std::map<std::string, nk_font *> fonts);
			virtual void renderUI(struct nk_context *ctx);
			
			REGISTER_COMPONENT_HPP
	
		};

	};

};

#endif
