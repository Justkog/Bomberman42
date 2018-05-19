// ------------------------------------------------------------	//
//																//
//																//
// ------------------------------------------------------------	//

#ifndef BACKGROUNDDRAWER_HPP
# define BACKGROUNDDRAWER_HPP

/*!
 * \file BackgroundDrawer.hpp
 * \brief Background du menu de lancement
 * \author jblondea
 */

#include "Core/Core.hpp"
#include "Core/Component/Component.hpp"
#include "Core/Component/IStart.hpp"
#include "Core/Component/IUI.hpp"
#include "Core/Component/IStartUI.hpp"

namespace Game
{
	namespace Component
	{
		class UIThemeManager;

		class BackgroundDrawer : public BeerEngine::Component::Component, 
									public BeerEngine::Component::IStart,
									public BeerEngine::Component::IStartUI,
									public BeerEngine::Component::IUI
		{
		public:

			BackgroundDrawer();
			BackgroundDrawer(const BackgroundDrawer &val);
			BackgroundDrawer(BeerEngine::GameObject *gameObject);

			virtual ~BackgroundDrawer( void );

			BackgroundDrawer & operator=( BackgroundDrawer const & rhs );
			friend std::ostream & operator<<(std::ostream & o, BackgroundDrawer const & i);

			virtual void start();
			virtual void startUI(struct nk_context *ctx, std::map<std::string, nk_font *> fonts);
			virtual void renderUI(struct nk_context *ctx);
	
			UIThemeManager	*uiManager;

			REGISTER_COMPONENT_HPP
		};

	};

};

#endif
