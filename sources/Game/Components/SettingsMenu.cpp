#define NK_INCLUDE_FONT_BAKING

#include "Game/Components/SettingsMenu.hpp"
#include "Game/Components/MainMenu.hpp"
#include "Game/Components/UIThemeManager.hpp"
#include "Core/Window.hpp"

namespace Game
{
	namespace Component
	{
// STATIC ########################################################

// ###############################################################

// CANONICAL #####################################################

/*SettingsMenu::SettingsMenu ( void )
{
	return ;
}*/

/*SettingsMenu::SettingsMenu ( SettingsMenu const & src )
{
	*this = src;
	return ;
}*/

SettingsMenu &				SettingsMenu::operator=( SettingsMenu const & rhs )
{
	if (this != &rhs)
	{
		// make stuff
	}
	return (*this);
}

SettingsMenu::~SettingsMenu ( void )
{
	return ;
}

// ###############################################################

// CONSTRUCTOR POLYMORPHISM ######################################

SettingsMenu::SettingsMenu(BeerEngine::GameObject *gameObject) :
Component(gameObject)
{
	
}

// ###############################################################

// OVERLOAD OPERATOR #############################################

std::ostream &				operator<<(std::ostream & o, SettingsMenu const & i)
{
	(void)i;
	return (o);
}

// ###############################################################

// PUBLIC METHOD #################################################

void SettingsMenu::start()
{
	std::cout << "SettingsMenu start" << std::endl;
	windowHeight = WINDOW_HEIGHT;
	windowWidth = WINDOW_WIDTH;
}

void SettingsMenu::setUI(struct nk_context *ctx)
{
	ctx->style.window = mWindow;
	ctx->style.text.color = nk_rgb(255,255,255);
	ctx->style.slider.bar_normal = nk_rgb(255,255,255);
	ctx->style.slider.bar_hover = nk_rgb(200,200,200);
	ctx->style.slider.bar_filled = nk_rgb(0,0,0);
}

void SettingsMenu::startUI(struct nk_context *ctx, std::map<std::string, nk_font *> fonts)
{
	std::cout << "start UI settings menu" << std::endl;
	mWindow = uiManager->defaultWindow;

	mWindow.fixed_background = nk_style_item_hide();
	// mWindow.padding = nk_vec2(0, 0);
	mWindow.spacing = nk_vec2(0, 10);
}

void SettingsMenu::renderUI(struct nk_context *ctx)
{
	uiManager->setThemeUI(ctx);
	setUI(ctx);
	float menuWidth = 640;
	float menuHeight = 375 + 5 * 10;
	float xOffset = 50;
	float yOffset = 100;
	auto window_rect = nk_rect(
		WINDOW_WIDTH / 2 - menuWidth / 2 + xOffset, 
		WINDOW_HEIGHT / 2 - menuHeight / 2 + yOffset, 
		menuWidth, 
		menuHeight
	);
	if (nk_begin(ctx, "Settings", window_rect, 0))
	{
		nk_layout_row_dynamic(ctx, 75, 2);

		std::stringstream ssHeight;
		ssHeight << "Height: " << windowHeight;
		nk_label(ctx, ssHeight.str().c_str(), NK_TEXT_LEFT);
		nk_slider_float(ctx, 0, &windowHeight, 2304.0f, 1.0f);

		std::stringstream ssWidth;
		ssWidth << "Width: " << windowWidth;
		nk_label(ctx, ssWidth.str().c_str(), NK_TEXT_LEFT);
		nk_slider_float(ctx, 0, &windowWidth, 4096.0f, 1.0f);

		nk_layout_row_dynamic(ctx, 75, 3);
		if (nk_group_begin(ctx, "column1", NK_WINDOW_BORDER)) { // column 1
			nk_group_end(ctx);
		}

		if (nk_group_begin(ctx, "column1", NK_WINDOW_BORDER)) { // column 1
			if (nk_button_label(ctx, "Setting 2"))
				fprintf(stdout, "Versus pressed\n");
			if (nk_button_label(ctx, "Back"))
			{
				this->setActive(false);
				mainMenu->setActive(true);
			}

			nk_group_end(ctx);
		}

		// if (nk_button_label(ctx, "Setting 2"))
		// 	fprintf(stdout, "Versus pressed\n");
		// if (nk_button_label(ctx, "Back"))
		// {
		// 	this->setActive(false);
		// 	mainMenu->setActive(true);
		// }
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
