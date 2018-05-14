// ------------------------------------------------------------	//
//																//
//																//
// ------------------------------------------------------------	//

#ifndef ITEMSUI_HPP
# define ITEMSUI_HPP

#include "Core/Core.hpp"
#include "Game/Game.hpp"
#include "Core/Component/Component.hpp"
#include "Core/Component/IStart.hpp"
#include "Core/Component/IUpdate.hpp"
#include "Core/Component/IStartUI.hpp"
#include "Core/Component/IUI.hpp"

namespace Game
{
	namespace Component
	{
		class ItemsUI : public BeerEngine::Component::Component, 
						public BeerEngine::Component::IStart, 
						public BeerEngine::Component::IUpdate, 
						public BeerEngine::Component::IStartUI, 
						public BeerEngine::Component::IUI
		{
		public:
			UIThemeManager	*uiManager;
			nk_style_item	shoeImage;
			nk_style_item	bombImage;
			nk_style_item	rangeImage;
			Player			*player;

			int				speed;
			int				bombs;
			int				range;

			// ItemsUI( void );
			// ItemsUI( ItemsUI const & src );
			ItemsUI(BeerEngine::GameObject *gameObject);

			virtual ~ItemsUI( void );

			ItemsUI & operator=( ItemsUI const & rhs );
			friend std::ostream & operator<<(std::ostream & o, ItemsUI const & i);

			virtual void start();
			virtual void update();
			virtual void fixedUpdate();
			virtual void startUI(struct nk_context *ctx, std::map<std::string, nk_font *> fonts);
			virtual void renderUI(struct nk_context *ctx);

			void drawItemInfo(struct nk_context *ctx, nk_style_item image, int itemInfo);
			void setUI(struct nk_context *ctx);

			void acknowledgePlayerDeath(glm::vec3 pos, int value);

			REGISTER_COMPONENT_HPP
		};

	};

};

#endif
