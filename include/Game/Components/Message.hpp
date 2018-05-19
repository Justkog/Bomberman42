// ------------------------------------------------------------	//
//																//
//																//
// ------------------------------------------------------------	//

#ifndef MESSAGE_HPP
# define MESSAGE_HPP

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
		class Message : public BeerEngine::Component::Component, 
						public BeerEngine::Component::IStart, 
						public BeerEngine::Component::IStartUI, 
						public BeerEngine::Component::IUI
		{
		private:
			// std::string					text;
			std::vector<std::string> 	lines;

			void buildLines(std::string text);
			
		public:
			UIThemeManager	*uiManager;
			nk_style_item	backGround;

			// Message( void );
			// Message( Message const & src );
			Message(BeerEngine::GameObject *gameObject);

			virtual ~Message( void );

			Message & operator=( Message const & rhs );
			friend std::ostream & operator<<(std::ostream & o, Message const & i);

			virtual void start();
			virtual void startUI(struct nk_context *ctx, std::map<std::string, nk_font *> fonts);
			virtual void renderUI(struct nk_context *ctx);

			void	updateDisplay(std::string text);
			
			REGISTER_COMPONENT_HPP
	
		};

	};

};

#endif
