#include "Game/Components/ItemsUI.hpp"
#include "Core/Window.hpp"
#include "Game/Components/UIThemeManager.hpp"

namespace Game
{
	namespace Component
	{
// STATIC ########################################################

// ###############################################################

// CANONICAL #####################################################

/*ItemsUI::ItemsUI ( void )
{
	return ;
}*/

/*ItemsUI::ItemsUI ( ItemsUI const & src )
{
	*this = src;
	return ;
}*/

ItemsUI &				ItemsUI::operator=( ItemsUI const & rhs )
{
	if (this != &rhs)
	{
		// make stuff
	}
	return (*this);
}

ItemsUI::~ItemsUI ( void )
{
	return ;
}

// ###############################################################

// CONSTRUCTOR POLYMORPHISM ######################################

ItemsUI::ItemsUI(BeerEngine::GameObject *gameObject) :
Component(gameObject)
{
	
}

// ###############################################################

// OVERLOAD OPERATOR #############################################

std::ostream &				operator<<(std::ostream & o, ItemsUI const & i)
{
	(void)i;
	return (o);
}

// ###############################################################

// PUBLIC METHOD #################################################

void ItemsUI::start()
{
	std::cout << "ItemsUI start" << std::endl;
	shoeImage = uiManager->loadSprite("assets/textures/shoe.png");
	bombImage = uiManager->loadSprite("assets/textures/bomb.png");
	rangeImage = uiManager->loadSprite("assets/textures/range.png");
}

void ItemsUI::startUI(struct nk_context *ctx, std::map<std::string, nk_font *> fonts)
{

}

void ItemsUI::setUI(struct nk_context *ctx)
{
	ctx->style.text.color = nk_rgb(255,255,255);
}

void ItemsUI::drawItemInfo(struct nk_context *ctx, nk_style_item image, int itemInfo)
{
	float rowHeight = 75;
	float imageSpaceWidth = 150;
	float targetRatio = imageSpaceWidth / rowHeight;
	float imageRatio = static_cast<float>(image.data.image.w) / static_cast<float>(image.data.image.h);

	if (imageRatio < targetRatio)
	{
		// image height remains rowHeight
		// need to recalculate imageWidth to make it the width of the center column
		float imageWidth = rowHeight * imageRatio;

		nk_layout_row_begin(ctx, NK_STATIC, rowHeight, 4);

		// left column to center image
		nk_layout_row_push(ctx, (imageSpaceWidth - imageWidth) / 2);
		ctx->style.window.fixed_background = nk_style_item_hide();
		if (nk_group_begin(ctx, "column1", NK_WINDOW_NO_SCROLLBAR | NK_WINDOW_NOT_INTERACTIVE)) { // column 1
			nk_group_end(ctx);
		}

		// column containing image
		nk_layout_row_push(ctx, imageWidth);
		ctx->style.window.fixed_background = image;
		if (nk_group_begin(ctx, "column1", NK_WINDOW_NO_SCROLLBAR | NK_WINDOW_NOT_INTERACTIVE)) { // column 1
			nk_group_end(ctx);
		}

		// right column to center image
		nk_layout_row_push(ctx, (imageSpaceWidth - imageWidth) / 2);
		ctx->style.window.fixed_background = nk_style_item_hide();
		if (nk_group_begin(ctx, "column1", NK_WINDOW_NO_SCROLLBAR | NK_WINDOW_NOT_INTERACTIVE)) { // column 1
			nk_group_end(ctx);
		}

		// last column to display item info
		std::stringstream ssInfo;
		ssInfo << itemInfo;
		nk_label(ctx, ssInfo.str().c_str(), NK_TEXT_LEFT);
	}
}

void ItemsUI::renderUI(struct nk_context *ctx)
{
	uiManager->setThemeUI(ctx);
	setUI(ctx);
	float panelWidth = 225;
	float panelHeight = 400;
	float xOffset = 0;
	float yOffset = 0;
	auto window_rect = nk_rect(
		BeerEngine::Window::GetInstance()->getWidth() - panelWidth, 
		yOffset, 
		panelWidth, 
		panelHeight
	);
	if (nk_begin(ctx, "Items", window_rect, NK_WINDOW_NO_SCROLLBAR | NK_WINDOW_NOT_INTERACTIVE | NK_WINDOW_BACKGROUND))
	{
		drawItemInfo(ctx, shoeImage, 0);
		drawItemInfo(ctx, bombImage, 0);
		drawItemInfo(ctx, rangeImage, 0);
	}
	nk_end(ctx);
	uiManager->resetToDefaultUI(ctx);
}

// ###############################################################

// GETTER METHOD #################################################

// ###############################################################

// SETTER METHOD #################################################

// ###############################################################

// PRIVATE METHOD ################################################

// ###############################################################

// EXCEPTION METHOD ##############################################

// ###############################################################

// EXTERNAL ######################################################

// ###############################################################
	}
}
