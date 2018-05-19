#include "Game/Components/AdventureMenu.hpp"
#include "Game/Components/AdventureContinueMenu.hpp"
#include "Game/Components/MainMenu.hpp"
#include "Game/Components/UIThemeManager.hpp"
#include "Game/Components/GameProgression.hpp"
#include "Core/Window.hpp"

namespace Game
{
	namespace Component
	{
// STATIC ########################################################

// ###############################################################

// CANONICAL #####################################################

/*AdventureMenu::AdventureMenu ( void )
{
	return ;
}*/

/*AdventureMenu::AdventureMenu ( AdventureMenu const & src )
{
	*this = src;
	return ;
}*/

AdventureMenu &				AdventureMenu::operator=( AdventureMenu const & rhs )
{
	if (this != &rhs)
	{
		// make stuff
	}
	return (*this);
}

AdventureMenu::~AdventureMenu ( void )
{
	return ;
}

// ###############################################################

// CONSTRUCTOR POLYMORPHISM ######################################

AdventureMenu::AdventureMenu(BeerEngine::GameObject *gameObject) :
Component(gameObject)
{
	
}

// ###############################################################

// OVERLOAD OPERATOR #############################################

std::ostream &				operator<<(std::ostream & o, AdventureMenu const & i)
{
	(void)i;
	return (o);
}

// ###############################################################

// PUBLIC METHOD #################################################

void AdventureMenu::start()
{
	std::cout << "AdventureMenu start" << std::endl;
	sceneLoader.name = "Level1";
}

void AdventureMenu::startUI(struct nk_context *ctx, std::map<std::string, nk_font *> fonts)
{
	
}

void AdventureMenu::renderUI(struct nk_context *ctx)
{
	uiManager->setThemeUI(ctx);

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
	ctx->style.window.spacing = nk_vec2(0, 10);
	if (nk_begin(ctx, "Adventure Menu", window_rect, NK_WINDOW_NO_SCROLLBAR))
	{
		nk_layout_row_dynamic(ctx, 75, 1);

		// for (auto it = maps.begin(); it != maps.end(); it++)
		// {
		// 	if (nk_button_label(ctx, it->name.c_str()))
		// 		BeerEngine::SceneManager::LoadScene(it->scenePath);
		// }
		if (nk_button_label(ctx, "New Game"))
		{
			sceneLoader.load();
		}
		if (nk_button_label(ctx, "Continue"))
		{
			this->setActive(false);
			continueMenu->setActive(true);
		}
		if (nk_button_label(ctx, "Reset"))
		{
			gameProgression->resetGameProgression();
		}
		if (nk_button_label(ctx, "Back"))
		{
			this->setActive(false);
			mainMenu->setActive(true);
		}
	}
	nk_end(ctx);

	uiManager->resetToDefaultUI(ctx);
}

nlohmann::json	AdventureMenu::serialize()
{
	auto j = Component::serialize();
	j.merge_patch({
		{"componentClass", type},
	});
	return j;
}

void AdventureMenu::deserialize(const nlohmann::json & j, BeerEngine::JsonLoader & loader)
{
	Component::deserialize(j, loader);
}

REGISTER_COMPONENT_CPP(AdventureMenu)

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
