#define NK_INCLUDE_FONT_BAKING
#include "Game/Assets.hpp"
#include "Core/Graphics/Texture.hpp"
#include "Game/Components/UIThemeManager.hpp"
#include "Game/Components/MainMenu.hpp"
#include "Game/Components/AdventureMenu.hpp"
#include "Game/Components/VersusMenu.hpp"
#include "Game/Components/SettingsMenu.hpp"
#include "Game/Components/Credits.hpp"
#include "Core/Window.hpp"
#include "Core/SceneManager.hpp"
#include "Game/SceneTest.hpp"
#include "Game/Level1.hpp"

namespace Game
{
	namespace Component
	{
// STATIC ########################################################

// ###############################################################

// CANONICAL #####################################################

MainMenu::MainMenu ( void )
{
	return ;
}

MainMenu::MainMenu ( MainMenu const & src )
{
	*this = src;
	return ;
}

MainMenu &				MainMenu::operator=( MainMenu const & rhs )
{
	(void) rhs;
	if (this != &rhs)
	{}
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
	// uiInit = true;
}

void MainMenu::setUI(struct nk_context *ctx)
{
	ctx->style.window = mWindow;
}

void MainMenu::startUI(struct nk_context *ctx, std::map<std::string, nk_font *> fonts)
{
	(void) ctx;
	(void) fonts;
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
		BeerEngine::Window::GetInstance()->getWidth() / 2 - menuWidth / 2 + xOffset, 
		BeerEngine::Window::GetInstance()->getHeight() / 2 - menuHeight / 2 + yOffset, 
		menuWidth, 
		menuHeight
	);
	if (nk_begin(ctx, "MainMenu", window_rect, NK_WINDOW_NO_SCROLLBAR))
	{
		nk_layout_row_dynamic(ctx, 75, 1);

		if (nk_button_label(ctx, "Adventure"))
		{
			this->setActive(false);
			adventureMenu->setActive(true);
			// fprintf(stdout, "Adventure pressed\n");
			// BeerEngine::SceneManager::LoadScene<Level1>();
		}
		if (nk_button_label(ctx, "Versus"))
		{
			this->setActive(false);
			versusMenu->setActive(true);
		}
		if (nk_button_label(ctx, "Settings"))
		{
			this->setActive(false);
			settingsMenu->setActive(true);
		}
		if (nk_button_label(ctx, "Credits"))
		{
			this->setActive(false);
			credits->setActive(true);
		}
		if (nk_button_label(ctx, "Exit"))
			BeerEngine::Window::GetInstance()->closeRequest();
	}
	nk_end(ctx);
	// if (uiInit)
	// {
	// 	nk_window_set_focus(ctx, )
	// 	uiInit = false;
	// }
	uiManager->resetToDefaultUI(ctx);
}

nlohmann::json	MainMenu::serialize()
{
	auto j = Component::serialize();
	j.merge_patch({
		{"componentClass", type},
		{"settingsMenu", settingsMenu->_serializationID},
		{"versusMenu", versusMenu->_serializationID},
		{"uiManager", uiManager->_serializationID},
	});
	return j;
}

void MainMenu::deserialize(const nlohmann::json & j, BeerEngine::JsonLoader & loader)
{
	Component::deserialize(j, loader);
	DESERIALIZE_BY_ID(this->settingsMenu, SettingsMenu, "settingsMenu", loader);
	DESERIALIZE_BY_ID(this->versusMenu, VersusMenu, "versusMenu", loader);
	DESERIALIZE_BY_ID(this->uiManager, UIThemeManager, "uiManager", loader);
}

REGISTER_COMPONENT_CPP(MainMenu)

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
