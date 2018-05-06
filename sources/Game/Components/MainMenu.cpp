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
	defaultBackground = ctx->style.window.fixed_background;
	defaultButtonBackground = ctx->style.button.normal;
}

void MainMenu::setUI(struct nk_context *ctx)
{
	ctx->style.window.fixed_background = menuBackground;
	ctx->style.button.normal = buttonBackground;
}

void MainMenu::resetToDefaultUI(struct nk_context *ctx)
{
	ctx->style.window.fixed_background = defaultBackground;
	ctx->style.button.normal = defaultButtonBackground;
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
	menuBackground = loadSprite("assets/textures/crate1_diffuse.png");
	buttonBackground = loadSprite("assets/textures/crate1_bump.png");
}

void MainMenu::renderUI(struct nk_context *ctx)
{
	setUI(ctx);
	float menuWidth = 320;
	float menuHeight = 430;
	auto window_rect = nk_rect(
		WINDOW_WIDTH / 2 - menuWidth / 2, 
		WINDOW_HEIGHT / 2 - menuHeight / 2, 
		menuWidth, 
		menuHeight
	);
	if (nk_begin(ctx, "Map", window_rect, NK_WINDOW_NO_SCROLLBAR))
	{
		nk_layout_row_dynamic(ctx, 50, 1);

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
