#include "Game/Components/MainMenu.hpp"
#include "Game/Assets.hpp"
#include "Core/Graphics/Texture.hpp"

namespace Game
{
	namespace Component
	{
// STATIC ########################################################

// ###############################################################

// CANONICAL #####################################################

/*MainMenu::MainMenu ( void )
{
	return ;
}*/

/*MainMenu::MainMenu ( MainMenu const & src )
{
	*this = src;
	return ;
}*/

MainMenu &				MainMenu::operator=( MainMenu const & rhs )
{
	if (this != &rhs)
	{
		// make stuff
	}
	return (*this);
}

MainMenu::~MainMenu ( void )
{
	return ;
}

// ###############################################################

// CONSTRUCTOR POLYMORPHISM ######################################

MainMenu::MainMenu(BeerEngine::GameObject *gameObject) :
Component(gameObject)
{
	
}

// ###############################################################

// OVERLOAD OPERATOR #############################################

std::ostream &				operator<<(std::ostream & o, MainMenu const & i)
{
	(void)i;
	return (o);
}

// ###############################################################

// PUBLIC METHOD #################################################

void MainMenu::start()
{
	std::cout << "MainMenu start" << std::endl;
}

void MainMenu::saveDefaultUI(struct nk_context *ctx)
{
	defaultWindow = ctx->style.window;
	defaultButton = ctx->style.button;
	mWindow = defaultWindow;
	mButton = defaultButton;
}

void MainMenu::setUI(struct nk_context *ctx)
{
	ctx->style.window = mWindow;
	ctx->style.button = mButton;

}

void MainMenu::resetToDefaultUI(struct nk_context *ctx)
{
	ctx->style.window = defaultWindow;
	ctx->style.button = defaultButton;
}

nk_style_item loadSprite(std::string spritePath)
{
	auto texture = Assets::GetTexture(spritePath);
	auto nk_image = nk_subimage_id(
		texture->getID(), 
		texture->getWidth(),
		texture->getHeight(), 
		nk_rect(0,0,texture->getWidth(),texture->getHeight()));
	return (nk_style_item_image(nk_image));
}

void MainMenu::startUI(struct nk_context *ctx)
{
	std::cout << "start UI" << std::endl;
	saveDefaultUI(ctx);
	// mWindow.fixed_background = loadSprite("assets/textures/crate1_diffuse.png");
	mWindow.fixed_background = nk_style_item_hide();
	// mWindow.background = nk_style_item_hide();
	// mWindow.padding = nk_vec2(0, 0);
	mWindow.spacing = nk_vec2(0, 10);
	// mButton.normal = 
	mButton.normal = loadSprite("assets/textures/button_normal.png");
}

void MainMenu::renderUI(struct nk_context *ctx)
{
	ctx->style.window.fixed_background = loadSprite("assets/textures/MainScreen.png");
	auto back_window_rect = nk_rect(
		0, 
		0, 
		WINDOW_WIDTH, 
		WINDOW_HEIGHT
	);

	if (nk_begin(ctx, "Background", back_window_rect, NK_WINDOW_NO_SCROLLBAR | NK_WINDOW_NOT_INTERACTIVE))
	{
		// just the background window
	}
	nk_end(ctx);

	setUI(ctx);
	float menuWidth = 320;
	float menuHeight = 375 + 5 * 10;
	float xOffset = 0;
	float yOffset = 100;
	auto window_rect = nk_rect(
		WINDOW_WIDTH / 2 - menuWidth / 2 + xOffset, 
		WINDOW_HEIGHT / 2 - menuHeight / 2 + yOffset, 
		menuWidth, 
		menuHeight
	);
	if (nk_begin(ctx, "Map", window_rect, NK_WINDOW_NO_SCROLLBAR))
	{
		nk_layout_row_dynamic(ctx, 75, 1);

		if (nk_button_label(ctx, "Adventure"))
			fprintf(stdout, "button pressed\n");
		if (nk_button_label(ctx, "Quick Match"))
			fprintf(stdout, "button 2 pressed\n");
		if (nk_button_label(ctx, "Settings"))
			fprintf(stdout, "button 2 pressed\n");
		if (nk_button_label(ctx, "Credits"))
			fprintf(stdout, "button 2 pressed\n");
		if (nk_button_label(ctx, "Exit"))
			fprintf(stdout, "button 2 pressed\n");
	}
	nk_end(ctx);
	resetToDefaultUI(ctx);
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
