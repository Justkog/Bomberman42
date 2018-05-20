// ------------------------------------------------------------	//
//																//
//																//
// ------------------------------------------------------------	//

#ifndef CREDITS_HPP
# define CREDITS_HPP

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
		class Credits : public BeerEngine::Component::Component, 
						public BeerEngine::Component::IStart, 
						public BeerEngine::Component::IStartUI, 
						public BeerEngine::Component::IUI
		{
		public:

			// Credits( void );
			// Credits( Credits const & src );
			Credits(BeerEngine::GameObject *gameObject);

			virtual ~Credits( void );

			Credits & operator=( Credits const & rhs );
			friend std::ostream & operator<<(std::ostream & o, Credits const & i);

			virtual void start();
			virtual void startUI(struct nk_context *ctx, std::map<std::string, nk_font *> fonts);
			virtual void renderUI(struct nk_context *ctx);
			
			REGISTER_COMPONENT_HPP
	
		};

	};

};

#endif
