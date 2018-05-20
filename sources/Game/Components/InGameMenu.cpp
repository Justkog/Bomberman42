#define NK_INCLUDE_FONT_BAKING
#include "Game/Components/InGameMenu.hpp"
#include "Game/Components/UIThemeManager.hpp"
#include "Core/Window.hpp"
#include "Core/SceneManager.hpp"
#include "Game/SceneMain.hpp"
#include "Game/Components/GameManager.hpp"

namespace Game
{
	namespace Component
	{
// STATIC ########################################################

// ###############################################################

// CANONICAL #####################################################

InGameMenu::InGameMenu ( void )
{
	return ;
}

InGameMenu::InGameMenu ( InGameMenu const & src )
{
	*this = src;
	return ;
}

InGameMenu &				InGameMenu::operator=( InGameMenu const & rhs )
{
	(void) rhs;
	if (this != &rhs)
	{}
	return (*this);
}

InGameMenu::~InGameMenu ( void )
{
	return ;
}

// ###############################################################

// CONSTRUCTOR POLYMORPHISM ######################################

InGameMenu::InGameMenu(BeerEngine::GameObject *gameObject) :
Component(gameObject)
{
	
}

// ###############################################################

// OVERLOAD OPERATOR #############################################

std::ostream &				operator<<(std::ostream & o, InGameMenu const & i)
{
	(void)i;
	return (o);
}

// ###############################################################

// PUBLIC METHOD #################################################

void InGameMenu::start()
{
	std::cout << "InGameMenu start" << std::endl;
}

void InGameMenu::enable()
{
	std::cout << "game menu enabled" << std::endl;
	GameManager::GetInstance().setPause(true);
}

void InGameMenu::disable()
{
	std::cout << "game menu disabled" << std::endl;
	GameManager::GetInstance().setPause(false);
}

void InGameMenu::setUI(struct nk_context *ctx)
{
	nk_style_set_font(ctx, &uiManager->available_fonts["smallMain"]->handle);
}

void InGameMenu::startUI(struct nk_context *ctx, std::map<std::string, nk_font *> fonts)
{
	(void) ctx;
	(void) fonts;
	std::cout << "start UI main menu" << std::endl;
}

void InGameMenu::renderUI(struct nk_context *ctx)
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
	if (nk_begin(ctx, "Menu", window_rect, NK_WINDOW_NO_SCROLLBAR))
	{
		nk_layout_row_dynamic(ctx, 75, 1);

		if (nk_button_label(ctx, "Resume"))
			this->setActive(false);
		if (nk_button_label(ctx, "Back to Main Menu"))
		{
			GameManager::GetInstance().setPause(false);
			BeerEngine::SceneManager::LoadScene<SceneMain>();
		}
	}
	nk_end(ctx);
	uiManager->resetToDefaultUI(ctx);
}

nlohmann::json	InGameMenu::serialize()
{
	auto j = Component::serialize();
	j.merge_patch({
		{"componentClass", type},
		{"uiManager", SERIALIZE_BY_ID(uiManager)},
	});
	return j;
}

void InGameMenu::deserialize(const nlohmann::json & j, BeerEngine::JsonLoader & loader)
{
	Component::deserialize(j, loader);
	DESERIALIZE_BY_ID(this->uiManager, UIThemeManager, "uiManager", loader);
}

REGISTER_COMPONENT_CPP(InGameMenu)

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
