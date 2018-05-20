#define NK_INCLUDE_FONT_BAKING
#include "Game/Components/Credits.hpp"
#include "Game/Components/UIThemeManager.hpp"
#include "Game/Components/MainMenu.hpp"
#include "Core/Window.hpp"

namespace Game
{
	namespace Component
	{
// STATIC ########################################################

// ###############################################################

// CANONICAL #####################################################

/*Credits::Credits ( void )
{
	return ;
}*/

/*Credits::Credits ( Credits const & src )
{
	*this = src;
	return ;
}*/

Credits &				Credits::operator=( Credits const & rhs )
{
	if (this != &rhs)
	{
		// make stuff
	}
	return (*this);
}

Credits::~Credits ( void )
{
	return ;
}

// ###############################################################

// CONSTRUCTOR POLYMORPHISM ######################################

Credits::Credits(BeerEngine::GameObject *gameObject) :
Component(gameObject)
{
	
}

// ###############################################################

// OVERLOAD OPERATOR #############################################

std::ostream &				operator<<(std::ostream & o, Credits const & i)
{
	(void)i;
	return (o);
}

// ###############################################################

// PUBLIC METHOD #################################################

void Credits::start()
{
	std::cout << "Credits start" << std::endl;
}

void Credits::startUI(struct nk_context *ctx, std::map<std::string, nk_font *> fonts)
{
	(void)ctx;
	(void)fonts;
	fortyTwoImage = uiManager->loadSprite("assets/textures/logo_42 white.png");
	bgImage = uiManager->loadSprite("assets/textures/inputsBackground.png");
}

void Credits::renderUI(struct nk_context *ctx)
{
	// Game created by jblondea, mgallo, mploux, qhonore and stmartin
	// School 42 Project
	std::string intro = "Game created by";
	// std::string autors = "jblondea mgallo mploux qhonore stmartin";
	std::vector<std::string> authors = {
		"jblondea",
		"mgallo",
		"mploux",
		"qhonore",
		"stmartin"
	};

	uiManager->setThemeUI(ctx);
	ctx->style.window.padding = nk_vec2(0, 0);
	ctx->style.window.spacing = nk_vec2(0, 0);
	ctx->style.text.color = nk_rgb(255,255,255);

	float creditsHeight = 400;
	float introHeight = 75;
	float authorsHeight = 50;
	
	float introTopMargin = 25;
	float authorsHorizontalPadding = 75;
	float logoTopPadding = 20;
	float logoBottomPadding = 60;
	
	float menuWidth = BeerEngine::Window::GetInstance()->getWidth() * 0.7;
	float menuHeight = creditsHeight + 75;
	float xOffset = 0;
	float yOffset = 100;
	auto window_rect = nk_rect(
		BeerEngine::Window::GetInstance()->getWidth() / 2 - menuWidth / 2 + xOffset, 
		BeerEngine::Window::GetInstance()->getHeight() / 2 - menuHeight / 2 + yOffset, 
		menuWidth, 
		menuHeight
	);
	// ctx->style.window.fixed_background = nk_style_item_hide();
	if (nk_begin(ctx, "Credits", window_rect, NK_WINDOW_NO_SCROLLBAR))
	{
		ctx->style.window.fixed_background = bgImage;
		// imageRatio = static_cast<float>(youLoseImage.data.image.w) / static_cast<float>(youLoseImage.data.image.h);
		// float imageHeight = menuWidth / imageRatio;
		nk_layout_row_dynamic(ctx, creditsHeight, 1);
		if (nk_group_begin(ctx, "CreditsBackground", NK_WINDOW_NO_SCROLLBAR | NK_WINDOW_NOT_INTERACTIVE | NK_WINDOW_BACKGROUND)) {
			ctx->style.window.fixed_background = nk_style_item_hide();
			nk_layout_row_dynamic(ctx, introTopMargin, 1);
			if (nk_group_begin(ctx, "Intro Top Margin", NK_WINDOW_NO_SCROLLBAR | NK_WINDOW_NOT_INTERACTIVE | NK_WINDOW_BACKGROUND)) {
				nk_group_end(ctx);
			}
			nk_layout_row_dynamic(ctx, introHeight, 1);
			nk_label(ctx, intro.c_str(), NK_TEXT_CENTERED);
			// nk_layout_row_dynamic(ctx, 75, 3);
			nk_layout_row_begin(ctx, NK_STATIC, authorsHeight, 3);
			nk_layout_row_push(ctx, authorsHorizontalPadding);
			ctx->style.window.fixed_background = nk_style_item_hide();
			if (nk_group_begin(ctx, "AuthorsEmpty", NK_WINDOW_NO_SCROLLBAR | NK_WINDOW_NOT_INTERACTIVE | NK_WINDOW_BACKGROUND)) {
				nk_group_end(ctx);
			}
			nk_layout_row_push(ctx, menuWidth - authorsHorizontalPadding * 2);
			if (nk_group_begin(ctx, "AuthorsGroup", NK_WINDOW_NO_SCROLLBAR | NK_WINDOW_NOT_INTERACTIVE | NK_WINDOW_BACKGROUND)) {
				nk_layout_row_dynamic(ctx, authorsHeight, 5);
				nk_style_set_font(ctx, &uiManager->available_fonts["smallMain"]->handle);
				for (auto author = authors.begin(); author != authors.end(); author++)
				{
					nk_label(ctx, author->c_str(), NK_TEXT_CENTERED);
				}
				nk_group_end(ctx);
			}

			float imageRatio = static_cast<float>(fortyTwoImage.data.image.w) / static_cast<float>(fortyTwoImage.data.image.h);
			float groupHeight = creditsHeight - introTopMargin - introHeight - authorsHeight - logoTopPadding - logoBottomPadding;
			float groupWidth = groupHeight * imageRatio;

			nk_layout_row_dynamic(ctx, logoTopPadding, 1);
			if (nk_group_begin(ctx, "Logo Top Padding", NK_WINDOW_NO_SCROLLBAR | NK_WINDOW_NOT_INTERACTIVE | NK_WINDOW_BACKGROUND)) {
				nk_group_end(ctx);
			}

			// nk_layout_row_dynamic(ctx, 200, 1);
			nk_layout_row_begin(ctx, NK_STATIC, groupHeight, 3);
			nk_layout_row_push(ctx, (menuWidth - groupWidth) / 2);
			ctx->style.window.fixed_background = nk_style_item_hide();
			if (nk_group_begin(ctx, "Logo Empty", NK_WINDOW_NO_SCROLLBAR | NK_WINDOW_NOT_INTERACTIVE | NK_WINDOW_BACKGROUND)) {
				nk_group_end(ctx);
			}
			nk_layout_row_push(ctx, groupWidth);
			ctx->style.window.fixed_background = fortyTwoImage;
			if (nk_group_begin(ctx, "42 Logo", NK_WINDOW_NO_SCROLLBAR | NK_WINDOW_NOT_INTERACTIVE | NK_WINDOW_BACKGROUND)) {
				nk_group_end(ctx);
			}

			nk_group_end(ctx);
		}
		nk_layout_row_dynamic(ctx, 75, 3);
		ctx->style.window.fixed_background = nk_style_item_hide();
		if (nk_group_begin(ctx, "CreditsEmpty", NK_WINDOW_NO_SCROLLBAR | NK_WINDOW_NOT_INTERACTIVE | NK_WINDOW_BACKGROUND)) {
			nk_group_end(ctx);
		}
		if (nk_button_label(ctx, "Back"))
		{
			this->setActive(false);
			mainMenu->setActive(true);
		}
	}

	// float imageRatio = static_cast<float>(backgroundImage.data.image.w) / static_cast<float>(backgroundImage.data.image.h);
	// float menuHeight = BeerEngine::Window::GetInstance()->getHeight() * 0.75f;
	// float menuWidth = menuHeight * imageRatio;
	// float xOffset = 0;
	// float yOffset = BeerEngine::Window::GetInstance()->getHeight() * 0.05f;
	// auto window_rect = nk_rect(
	// 	BeerEngine::Window::GetInstance()->getWidth() / 2 - menuWidth / 2 + xOffset, 
	// 	BeerEngine::Window::GetInstance()->getHeight() / 2 - menuHeight / 2 + yOffset, 
	// 	menuWidth, 
	// 	menuHeight
	// );
	// ctx->style.window.fixed_background = backgroundImage;
	// if (nk_begin(ctx, "GameOverBackground", window_rect, NK_WINDOW_NO_SCROLLBAR | NK_WINDOW_NOT_INTERACTIVE | NK_WINDOW_BACKGROUND))
	// {
	// 	nk_layout_row_dynamic(ctx, 75, 1);
	// }
	// nk_end(ctx);

	// menuWidth *= 0.5f;
	// window_rect = nk_rect(
	// 	BeerEngine::Window::GetInstance()->getWidth() / 2 - menuWidth / 2 + xOffset, 
	// 	BeerEngine::Window::GetInstance()->getHeight() / 2 - menuHeight / 2 + yOffset, 
	// 	menuWidth, 
	// 	menuHeight
	// );
	// ctx->style.window.fixed_background = nk_style_item_hide();
	// if (nk_begin(ctx, "GameOverMenu", window_rect, NK_WINDOW_NO_SCROLLBAR))
	// {
	// 	ctx->style.window.fixed_background = youLoseImage;
	// 	imageRatio = static_cast<float>(youLoseImage.data.image.w) / static_cast<float>(youLoseImage.data.image.h);
	// 	float imageHeight = menuWidth / imageRatio;
	// 	nk_layout_row_dynamic(ctx, imageHeight, 1);
	// 	if (nk_group_begin(ctx, "GameOverTitle", NK_WINDOW_NO_SCROLLBAR)) {
	// 		nk_group_end(ctx);
	// 	}

	// 	float buttonsSpacing = BeerEngine::Window::GetInstance()->getHeight() * 0.01f;
	// 	float buttonsFrameHeight = imageHeight * 2 + buttonsSpacing * 2;
		
	// 	ctx->style.window.fixed_background = nk_style_item_hide();
	// 	nk_layout_row_dynamic(ctx, menuHeight - imageHeight - buttonsFrameHeight, 1);
	// 	if (nk_group_begin(ctx, "GameOverSeparator", NK_WINDOW_NO_SCROLLBAR)) {
	// 		nk_group_end(ctx);
	// 	}

	// 	ctx->style.window.spacing = nk_vec2(0, buttonsSpacing);
	// 	nk_layout_row_dynamic(ctx, buttonsFrameHeight, 1);
	// 	if (nk_group_begin(ctx, "GameOverButtons", NK_WINDOW_NO_SCROLLBAR)) {
	// 		nk_layout_row_dynamic(ctx, imageHeight, 1);
	// 		if (nk_button_label(ctx, "Retry"))
	// 		{
	// 			GameManager::GetInstance().setPause(false);
	// 			sceneLoader.load();
	// 		// BeerEngine::SceneManager::LoadScene<SceneTest>();
	// 			// BeerEngine::SceneManager::LoadScene("assets/scenes/level1.scene");
	// 		}
	// 		if (nk_button_label(ctx, "Rage Quit"))
	// 		{
	// 			GameManager::GetInstance().setPause(false);
	// 			BeerEngine::SceneManager::LoadScene<SceneMain>();
	// 			// BeerEngine::SceneManager::LoadScene("assets/scenes/main.scene");
	// 		}
	// 		nk_group_end(ctx);
	// 	}

	// }
	nk_end(ctx);
	uiManager->resetToDefaultUI(ctx);
}

nlohmann::json	Credits::serialize()
{
	auto j = Component::serialize();
	j.merge_patch({
		{"componentClass", type},
	});
	return j;
}

void Credits::deserialize(const nlohmann::json & j, BeerEngine::JsonLoader & loader)
{
	Component::deserialize(j, loader);
}

REGISTER_COMPONENT_CPP(Credits)

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
