// ------------------------------------------------------------	//
//																//
//																//
// ------------------------------------------------------------	//

#ifndef STARTTIMERUI_HPP
# define STARTTIMERUI_HPP

/*!
 * \file StartTimerUI.hpp
 * \brief Component en charge de l'affichage du timer de lancement de partie.
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
		class StartTimerUI : public BeerEngine::Component::Component, 
						public BeerEngine::Component::IStart, 
						public BeerEngine::Component::IStartUI, 
						public BeerEngine::Component::IUI
		{
		public:
			UIThemeManager	*uiManager;
			std::string		text;

			StartTimerUI();
			StartTimerUI(const StartTimerUI &val);
			StartTimerUI(BeerEngine::GameObject *gameObject);

			virtual ~StartTimerUI( void );

			StartTimerUI & operator=( StartTimerUI const & rhs );
			friend std::ostream & operator<<(std::ostream & o, StartTimerUI const & i);

			virtual void start();
			virtual void startUI(struct nk_context *ctx, std::map<std::string, nk_font *> fonts);
			virtual void renderUI(struct nk_context *ctx);

			void	updateDisplay(std::string text);
			
			REGISTER_COMPONENT_HPP
	
		};

	};

};

#endif
