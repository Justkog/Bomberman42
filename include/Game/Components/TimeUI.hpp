// ------------------------------------------------------------	//
//																//
//																//
// ------------------------------------------------------------	//

#ifndef TIMEUI_HPP
# define TIMEUI_HPP

/*!
 * \file TimeUI.hpp
 * \brief Affichage du temps en cours de partie.
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
		class TimeUI : public BeerEngine::Component::Component, 
						public BeerEngine::Component::IStart,
						public BeerEngine::Component::IStartUI,
						public BeerEngine::Component::IUI
		{
		private:
			double 			_startTimeSinceStartup;
			bool			_started;

			TimeUI();
			TimeUI(const TimeUI &val);
			TimeUI & operator=( TimeUI const & rhs );

		public:
			UIThemeManager	*uiManager;
			nk_style_item	backGround;
			nk_style_item	tvScreen;
			double timeSinceGameStart;

			TimeUI(BeerEngine::GameObject *gameObject);

			virtual ~TimeUI( void );

			friend std::ostream & operator<<(std::ostream & o, TimeUI const & i);

			virtual void start();
			virtual void startUI(struct nk_context *ctx, std::map<std::string, nk_font *> fonts);
			virtual void renderUI(struct nk_context *ctx);

			void setUI(struct nk_context *ctx);

			void startClock();
	
			REGISTER_COMPONENT_HPP

		};

	};

};

#endif
