// ------------------------------------------------------------	//
//																//
//																//
// ------------------------------------------------------------	//

#ifndef ADVENTURECONTINUEMENU_HPP
# define ADVENTURECONTINUEMENU_HPP

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
		class AdventureContinueMenu : public BeerEngine::Component::Component, 
						public BeerEngine::Component::IStart, 
						public BeerEngine::Component::IStartUI, 
						public BeerEngine::Component::IUI
		{
		public:
			UIThemeManager					*uiManager;
			AdventureMenu					*adventureMenu;
			GameProgression					*gameProgression;
			std::vector<Game::SceneLoader>	availableLevels;

			// AdventureContinueMenu( void );
			// AdventureContinueMenu( AdventureContinueMenu const & src );
			AdventureContinueMenu(BeerEngine::GameObject *gameObject);

			virtual ~AdventureContinueMenu( void );

			AdventureContinueMenu & operator=( AdventureContinueMenu const & rhs );
			friend std::ostream & operator<<(std::ostream & o, AdventureContinueMenu const & i);

			virtual void start();
			virtual void startUI(struct nk_context *ctx, std::map<std::string, nk_font *> fonts);
			virtual void renderUI(struct nk_context *ctx);

			void updateAvailableLevels();
			
			REGISTER_COMPONENT_HPP
	
		};

	};

};

#endif
