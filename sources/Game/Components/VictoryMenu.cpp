#include "Game/Components/VictoryMenu.hpp"
#include "Game/Components/GameManager.hpp"
#include "Game/Components/UIThemeManager.hpp"
#include "Core/Window.hpp"
#include "Core/SceneManager.hpp"
#include "Game/SceneTest.hpp"
#include "Game/SceneMain.hpp"
#include "Core/SceneManager.hpp"
#include "Game/Level1.hpp"
#include "Game/Level2.hpp"

namespace Game
{
	namespace Component
	{
// STATIC ########################################################

// ###############################################################

// CANONICAL #####################################################

/*VictoryMenu::VictoryMenu ( void )
{
	return ;
}*/

/*VictoryMenu::VictoryMenu ( VictoryMenu const & src )
{
	*this = src;
	return ;
}*/

VictoryMenu &				VictoryMenu::operator=( VictoryMenu const & rhs )
{
	if (this != &rhs)
	{
		// make stuff
	}
	return (*this);
}

VictoryMenu::~VictoryMenu ( void )
{
	return ;
}

// ###############################################################

// CONSTRUCTOR POLYMORPHISM ######################################

VictoryMenu::VictoryMenu(BeerEngine::GameObject *gameObject) :
Component(gameObject)
{
	
}

// ###############################################################

// OVERLOAD OPERATOR #############################################

std::ostream &				operator<<(std::ostream & o, VictoryMenu const & i)
{
	(void)i;
	return (o);
}

// ###############################################################

// PUBLIC METHOD #################################################

void VictoryMenu::start()
{
	std::cout << "VictoryMenu start" << std::endl;
	backgroundImage = uiManager->loadSprite("assets/textures/victoryBackground.png");
	titleImage = uiManager->loadSprite("assets/textures/You-win.png");
}

void VictoryMenu::startUI(struct nk_context *ctx, std::map<std::string, nk_font *> fonts)
{
	
}

void VictoryMenu::renderUI(struct nk_context *ctx)
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
	if (nk_begin(ctx, "VictoryBackground", window_rect, NK_WINDOW_NO_SCROLLBAR | NK_WINDOW_NOT_INTERACTIVE | NK_WINDOW_BACKGROUND))
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
	if (nk_begin(ctx, "VictoryMenu", window_rect, NK_WINDOW_NO_SCROLLBAR))
	{
		ctx->style.window.fixed_background = titleImage;
		imageRatio = static_cast<float>(titleImage.data.image.w) / static_cast<float>(titleImage.data.image.h);
		float imageHeight = menuWidth / imageRatio;
		nk_layout_row_dynamic(ctx, imageHeight, 1);
		if (nk_group_begin(ctx, "VictoryTitle", NK_WINDOW_NO_SCROLLBAR)) {
			nk_group_end(ctx);
		}

		float buttonsSpacing = BeerEngine::Window::GetInstance()->getHeight() * 0.01f;
		float buttonsFrameHeight = imageHeight * 2 + buttonsSpacing * 2;
		
		ctx->style.window.fixed_background = nk_style_item_hide();
		nk_layout_row_dynamic(ctx, menuHeight - imageHeight - buttonsFrameHeight, 1);
		if (nk_group_begin(ctx, "VictorySeparator", NK_WINDOW_NO_SCROLLBAR)) {
			nk_group_end(ctx);
		}

		ctx->style.window.spacing = nk_vec2(0, buttonsSpacing);
		nk_layout_row_dynamic(ctx, buttonsFrameHeight, 1);
		if (nk_group_begin(ctx, "VictoryButtons", NK_WINDOW_NO_SCROLLBAR)) {
			nk_layout_row_dynamic(ctx, imageHeight, 1);
			if (nk_button_label(ctx, "Next Level"))
			{
				GameManager::GetInstance().setPause(false);
				sceneLoader.load();
				// BeerEngine::SceneManager::LoadScene<SceneTest>();
				// BeerEngine::SceneManager::LoadScene("assets/scenes/level2.scene");
			}
			if (nk_button_label(ctx, "Quit in peace"))
			{
				GameManager::GetInstance().setPause(false);
				BeerEngine::SceneManager::LoadScene<SceneMain>();
				// BeerEngine::SceneManager::LoadScene("assets/scenes/main.scene");
			}
			nk_group_end(ctx);
		}

	}
	nk_end(ctx);
	uiManager->resetToDefaultUI(ctx);
}

void VictoryMenu::enable()
{
	GameManager::GetInstance().setPause(true);
}

nlohmann::json	VictoryMenu::serialize()
{
	auto j = Component::serialize();
	j.merge_patch({
		{"componentClass", type},
		{"uiManager", SERIALIZE_BY_ID(uiManager)},
	});
	return j;
}

void VictoryMenu::deserialize(const nlohmann::json & j, BeerEngine::JsonLoader & loader)
{
	Component::deserialize(j, loader);
	DESERIALIZE_BY_ID(this->uiManager, UIThemeManager, "uiManager", loader);
}

REGISTER_COMPONENT_CPP(VictoryMenu)

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
