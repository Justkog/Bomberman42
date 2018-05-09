#define NK_INCLUDE_FONT_BAKING
#include "Game/Assets.hpp"
#include "Core/Graphics/Texture.hpp"
#include "Game/Components/UIThemeManager.hpp"
#include "Game/Components/MainMenu.hpp"
#include "Game/Components/SettingsMenu.hpp"
#include "Core/Window.hpp"
#include "Core/SceneManager.hpp"
#include "Game/SceneTest.hpp"

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

void MainMenu::setUI(struct nk_context *ctx)
{
	ctx->style.window = mWindow;
}

void MainMenu::startUI(struct nk_context *ctx, std::map<std::string, nk_font *> fonts)
{
	std::cout << "start UI main menu" << std::endl;
	mWindow = uiManager->defaultWindow;

	mWindow.fixed_background = nk_style_item_hide();
	// mWindow.padding = nk_vec2(0, 0);
	mWindow.spacing = nk_vec2(0, 10);
}

void MainMenu::renderUI(struct nk_context *ctx)
{
	uiManager->setThemeUI(ctx);
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
			fprintf(stdout, "Adventure pressed\n");
		if (nk_button_label(ctx, "Versus"))
		{
			fprintf(stdout, "Versus pressed\n");
			BeerEngine::SceneManager::LoadScene<SceneTest>();
		}
		if (nk_button_label(ctx, "Settings"))
		{
			this->setActive(false);
			settingsMenu->setActive(true);
		}
		if (nk_button_label(ctx, "Credits"))
			fprintf(stdout, "Credits pressed\n");
		if (nk_button_label(ctx, "Exit"))
			BeerEngine::Window::GetInstance()->closeRequest();
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
