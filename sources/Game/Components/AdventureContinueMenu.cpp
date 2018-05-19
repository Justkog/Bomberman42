#include "Game/Components/AdventureContinueMenu.hpp"
#include "Game/Components/AdventureMenu.hpp"
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

/*AdventureContinueMenu::AdventureContinueMenu ( void )
{
	return ;
}*/

/*AdventureContinueMenu::AdventureContinueMenu ( AdventureContinueMenu const & src )
{
	*this = src;
	return ;
}*/

AdventureContinueMenu &				AdventureContinueMenu::operator=( AdventureContinueMenu const & rhs )
{
	if (this != &rhs)
	{
		// make stuff
	}
	return (*this);
}

AdventureContinueMenu::~AdventureContinueMenu ( void )
{
	return ;
}

// ###############################################################

// CONSTRUCTOR POLYMORPHISM ######################################

AdventureContinueMenu::AdventureContinueMenu(BeerEngine::GameObject *gameObject) :
Component(gameObject)
{
	
}

// ###############################################################

// OVERLOAD OPERATOR #############################################

std::ostream &				operator<<(std::ostream & o, AdventureContinueMenu const & i)
{
	(void)i;
	return (o);
}

// ###############################################################

// PUBLIC METHOD #################################################

void AdventureContinueMenu::updateAvailableLevels()
{
	availableLevels.clear();
	auto unlockedLevels = gameProgression->gameProgressionContainer.unlockedLevels;
	for (auto it = unlockedLevels.begin(); it != unlockedLevels.end(); it++)
	{
		Game::SceneLoader loader;
		loader.name = *it;
		availableLevels.push_back(loader);
	}
}

void AdventureContinueMenu::start()
{
	std::cout << "AdventureContinueMenu start" << std::endl;
	updateAvailableLevels();
	gameProgression->onChange.bind(&AdventureContinueMenu::updateAvailableLevels, this);
}

void AdventureContinueMenu::startUI(struct nk_context *ctx, std::map<std::string, nk_font *> fonts)
{
	
}

void AdventureContinueMenu::renderUI(struct nk_context *ctx)
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

		struct nk_vec2 oldPadding = ctx->style.window.padding;
		struct nk_vec2 oldGroupPadding = ctx->style.window.group_padding;
		ctx->style.window.padding.y = 0;
		// ctx->style.window.padding = nk_vec2(0, 0);
		ctx->style.window.group_padding = nk_vec2(0, 0);
		
		nk_layout_row_dynamic(ctx, 75 * 4 + 10 * 3, 1);
		if (nk_group_begin(ctx, "Adventure Levels", 0)) {
			nk_layout_row_dynamic(ctx, 75, 1);
			for (auto it = availableLevels.begin(); it != availableLevels.end(); it++)
			{
				if (nk_button_label(ctx, it->name.c_str()))
					it->load();
			}
			nk_group_end(ctx);
		}
		ctx->style.window.padding = oldPadding;
		ctx->style.window.group_padding = oldGroupPadding;

		// for (auto it = availableLevels.begin(); it != availableLevels.end(); it++)
		// {
		// 	if (nk_button_label(ctx, it->name.c_str()))
		// 		it->load();
		// }
		// if (nk_button_label(ctx, "Level1"))
		// {

		// }
		// if (nk_button_label(ctx, "Level2"))
		// {

		// }
		nk_layout_row_dynamic(ctx, 75, 1);
		if (nk_button_label(ctx, "Back"))
		{
			this->setActive(false);
			adventureMenu->setActive(true);
		}
	}
	nk_end(ctx);

	uiManager->resetToDefaultUI(ctx);
}

nlohmann::json	AdventureContinueMenu::serialize()
{
	auto j = Component::serialize();
	j.merge_patch({
		{"componentClass", type},
	});
	return j;
}

void AdventureContinueMenu::deserialize(const nlohmann::json & j, BeerEngine::JsonLoader & loader)
{
	Component::deserialize(j, loader);
}

REGISTER_COMPONENT_CPP(AdventureContinueMenu)

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
