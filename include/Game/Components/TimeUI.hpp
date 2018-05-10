// ------------------------------------------------------------	//
//																//
//																//
// ------------------------------------------------------------	//

#ifndef TIMEUI_HPP
# define TIMEUI_HPP

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
		public:
			UIThemeManager	*uiManager;

			// TimeUI( void );
			// TimeUI( TimeUI const & src );
			TimeUI(BeerEngine::GameObject *gameObject);

			virtual ~TimeUI( void );

			TimeUI & operator=( TimeUI const & rhs );
			friend std::ostream & operator<<(std::ostream & o, TimeUI const & i);

			virtual void start();
			virtual void startUI(struct nk_context *ctx, std::map<std::string, nk_font *> fonts);
			virtual void renderUI(struct nk_context *ctx);

			void setUI(struct nk_context *ctx);
	
		};

	};

};

#endif
