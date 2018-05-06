// ------------------------------------------------------------	//
//																//
//																//
// ------------------------------------------------------------	//

#ifndef MAINMENU_HPP
# define MAINMENU_HPP

#include "Core/Core.hpp"
#include "Core/Component/Component.hpp"
#include "Core/Component/IStart.hpp"
#include "Core/Component/IStartUI.hpp"
#include "Core/Component/IUI.hpp"

namespace Game
{
	namespace Component
	{
		class MainMenu : public BeerEngine::Component::Component, 
						public BeerEngine::Component::IStart,
						public BeerEngine::Component::IStartUI,
						public BeerEngine::Component::IUI

		{
		public:
			nk_style_item defaultBackground;
			nk_style_item menuBackground;

			nk_style_item defaultButtonBackground;
			nk_style_item buttonBackground;

			// MainMenu( void );
			// MainMenu( MainMenu const & src );
			MainMenu(BeerEngine::GameObject *gameObject);

			virtual ~MainMenu( void );

			MainMenu & operator=( MainMenu const & rhs );
			friend std::ostream & operator<<(std::ostream & o, MainMenu const & i);

			virtual void start();
			virtual void startUI(struct nk_context *ctx);
			virtual void renderUI(struct nk_context *ctx);

			void saveDefaultUI(struct nk_context *ctx);
			void setUI(struct nk_context *ctx);
			void resetToDefaultUI(struct nk_context *ctx);
		};

	};

};

#endif
