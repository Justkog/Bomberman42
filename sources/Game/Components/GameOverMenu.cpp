#include "Game/Components/GameOverMenu.hpp"
#include "Game/Components/GameManager.hpp"
#include "Game/Components/UIThemeManager.hpp"
#include "Core/Window.hpp"
#include "Core/SceneManager.hpp"

namespace Game
{
	namespace Component
	{
// STATIC ########################################################

// ###############################################################

// CANONICAL #####################################################

/*GameOverMenu::GameOverMenu ( void )
{
	return ;
}*/

/*GameOverMenu::GameOverMenu ( GameOverMenu const & src )
{
	*this = src;
	return ;
}*/

GameOverMenu &				GameOverMenu::operator=( GameOverMenu const & rhs )
{
	if (this != &rhs)
	{
		// make stuff
	}
	return (*this);
}

GameOverMenu::~GameOverMenu ( void )
{
	return ;
}

// ###############################################################

// CONSTRUCTOR POLYMORPHISM ######################################

GameOverMenu::GameOverMenu(BeerEngine::GameObject *gameObject) :
Component(gameObject)
{
	
}

// ###############################################################

// OVERLOAD OPERATOR #############################################

std::ostream &				operator<<(std::ostream & o, GameOverMenu const & i)
{
	(void)i;
	return (o);
}

// ###############################################################

// PUBLIC METHOD #################################################

void GameOverMenu::start()
{
	std::cout << "GameOverMenu start" << std::endl;
	backgroundImage = uiManager->loadSprite("assets/textures/gameOverBackground.png");
	youLoseImage = uiManager->loadSprite("assets/textures/You-lose.png");
}

void GameOverMenu::startUI(struct nk_context *ctx, std::map<std::string, nk_font *> fonts)
{
	
}

void GameOverMenu::renderUI(struct nk_context *ctx)
{
	uiManager->setThemeUI(ctx);
	ctx->style.window.padding = nk_vec2(0, 0);
	ctx->style.window.spacing = nk_vec2(0, 0);
	

	float imageRatio = static_cast<float>(backgroundImage.data.image.w) / static_cast<float>(backgroundImage.data.image.h);
	float menuHeight = BeerEngine::Window::GetInstance()->getHeight() * 0.75f;
	float menuWidth = menuHeight * imageRatio;
	float xOffset = 0;
	float yOffset = BeerEngine::Window::GetInstance()->getHeight() * 0.05f;
	auto window_rect = nk_rect(
		BeerEngine::Window::GetInstance()->getWidth() / 2 - menuWidth / 2 + xOffset, 
		BeerEngine::Window::GetInstance()->getHeight() / 2 - menuHeight / 2 + yOffset, 
		menuWidth, 
		menuHeight
	);
	ctx->style.window.fixed_background = backgroundImage;
	if (nk_begin(ctx, "GameOverBackground", window_rect, NK_WINDOW_NO_SCROLLBAR | NK_WINDOW_NOT_INTERACTIVE | NK_WINDOW_BACKGROUND))
	{
		nk_layout_row_dynamic(ctx, 75, 1);
	}
	nk_end(ctx);

	menuWidth *= 0.5f;
	window_rect = nk_rect(
		BeerEngine::Window::GetInstance()->getWidth() / 2 - menuWidth / 2 + xOffset, 
		BeerEngine::Window::GetInstance()->getHeight() / 2 - menuHeight / 2 + yOffset, 
		menuWidth, 
		menuHeight
	);
	ctx->style.window.fixed_background = nk_style_item_hide();
	if (nk_begin(ctx, "GameOverMenu", window_rect, NK_WINDOW_NO_SCROLLBAR))
	{
		ctx->style.window.fixed_background = youLoseImage;
		imageRatio = static_cast<float>(youLoseImage.data.image.w) / static_cast<float>(youLoseImage.data.image.h);
		float imageHeight = menuWidth / imageRatio;
		nk_layout_row_dynamic(ctx, imageHeight, 1);
		if (nk_group_begin(ctx, "GameOverTitle", NK_WINDOW_NO_SCROLLBAR)) {
			nk_group_end(ctx);
		}

		float buttonsSpacing = BeerEngine::Window::GetInstance()->getHeight() * 0.01f;
		float buttonsFrameHeight = imageHeight * 2 + buttonsSpacing * 2;
		
		ctx->style.window.fixed_background = nk_style_item_hide();
		nk_layout_row_dynamic(ctx, menuHeight - imageHeight - buttonsFrameHeight, 1);
		if (nk_group_begin(ctx, "GameOverSeparator", NK_WINDOW_NO_SCROLLBAR)) {
			nk_group_end(ctx);
		}

		ctx->style.window.spacing = nk_vec2(0, buttonsSpacing);
		nk_layout_row_dynamic(ctx, buttonsFrameHeight, 1);
		if (nk_group_begin(ctx, "GameOverButtons", NK_WINDOW_NO_SCROLLBAR)) {
			nk_layout_row_dynamic(ctx, imageHeight, 1);
			if (nk_button_label(ctx, "Retry"))
			{
				GameManager::GetInstance().setPause(false);
				BeerEngine::SceneManager::LoadScene("assets/scenes/level1.scene");
			}
			if (nk_button_label(ctx, "Rage Quit"))
			{
				GameManager::GetInstance().setPause(false);
				BeerEngine::SceneManager::LoadScene("assets/scenes/main.scene");
			}
			nk_group_end(ctx);
		}

	}
	nk_end(ctx);
	uiManager->resetToDefaultUI(ctx);
}

void GameOverMenu::enable()
{
	GameManager::GetInstance().setPause(true);
}


nlohmann::json	GameOverMenu::serialize()
{
	auto j = Component::serialize();
	j.merge_patch({
		{"componentClass", type},
	});
	return j;
}

void GameOverMenu::deserialize(const nlohmann::json & j, BeerEngine::JsonLoader & loader)
{
	Component::deserialize(j, loader);
}

REGISTER_COMPONENT_CPP(GameOverMenu)

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
