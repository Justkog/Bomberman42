// ------------------------------------------------------------	//
//																//
//																//
// ------------------------------------------------------------	//

#ifndef VERSUSMENU_HPP
# define VERSUSMENU_HPP

/*!
 * \file VersusMenu.hpp
 * \brief Affichage du menu Versus.
 * \author jblondea
 */

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
		struct MapInfo
		{
			std::string name;
			std::string scenePath;
		};

		class VersusMenu : public BeerEngine::Component::Component, 
						public BeerEngine::Component::IStart, 
						public BeerEngine::Component::IStartUI, 
						public BeerEngine::Component::IUI
		{
		public:
			UIThemeManager			*uiManager;
			MainMenu				*mainMenu;
			std::vector<MapInfo> 	maps;

			// VersusMenu( void );
			// VersusMenu( VersusMenu const & src );
			VersusMenu(BeerEngine::GameObject *gameObject);

			virtual ~VersusMenu( void );

			VersusMenu & operator=( VersusMenu const & rhs );
			friend std::ostream & operator<<(std::ostream & o, VersusMenu const & i);

			virtual void start();
			virtual void startUI(struct nk_context *ctx, std::map<std::string, nk_font *> fonts);
			virtual void renderUI(struct nk_context *ctx);
	
			REGISTER_COMPONENT_HPP
		};

	};

};

#endif
