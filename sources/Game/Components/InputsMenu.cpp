#define NK_INCLUDE_FONT_BAKING
#include "Game/Components/InputsMenu.hpp"
#include "Game/Components/SettingsMenu.hpp"
#include "Game/Components/UIThemeManager.hpp"
#include "Game/Input.hpp"
#include "Core/Input.hpp"

namespace Game
{
	namespace Component
	{
// STATIC ########################################################

// ###############################################################

// CANONICAL #####################################################

/*InputsMenu::InputsMenu ( void )
{
	return ;
}*/

/*InputsMenu::InputsMenu ( InputsMenu const & src )
{
	*this = src;
	return ;
}*/

InputsMenu &				InputsMenu::operator=( InputsMenu const & rhs )
{
	if (this != &rhs)
	{
		// make stuff
	}
	return (*this);
}

InputsMenu::~InputsMenu ( void )
{
	return ;
}

// ###############################################################

// CONSTRUCTOR POLYMORPHISM ######################################

InputsMenu::InputsMenu(BeerEngine::GameObject *gameObject) :
Component(gameObject)
{
	
}

// ###############################################################

// OVERLOAD OPERATOR #############################################

std::ostream &				operator<<(std::ostream & o, InputsMenu const & i)
{
	(void)i;
	return (o);
}

// ###############################################################

// PUBLIC METHOD #################################################

void InputsMenu::setMapKey(std::string label, std::string key)
{
	strcpy(inputs[label].text, key.c_str());
	inputs[label].text_len = 1;
	inputs[label].waitingBind = false;
	inputsList.push_back(label);
}

void InputsMenu::start()
{
	std::cout << "InputsMenu start" << std::endl;
	setMapKey("move up", "w");
	setMapKey("move down", "s");
	setMapKey("move left", "a");
	setMapKey("move right", "d");
	setMapKey("bomb", " ");
	// setMapKey("move right", "d");
	// setMapKey("move right", "d");
	// setMapKey("move right", "d");
	// setMapKey("move right", "d");
	// setMapKey("move right", "d");
	// setMapKey("move right", "d");
	// setMapKey("move right", "d");
	// setMapKey("move right", "d");
	// setMapKey("move right", "d");
	
}

void InputsMenu::setUI(struct nk_context *ctx)
{
	// ctx->style.window.fixed_background = nk_style_item_hide();
	ctx->style.window.fixed_background = uiManager->loadSprite("assets/textures/inputsBackground.png");
	ctx->style.window.spacing = nk_vec2(10, 10);
	ctx->style.window.padding = nk_vec2(30, 30);

	ctx->style.text.color = nk_rgb(255, 102, 0);
	ctx->style.slider.bar_normal = nk_rgb(255,255,255);
	ctx->style.slider.bar_hover = nk_rgb(200,200,200);
	ctx->style.slider.bar_filled = nk_rgb(0,0,0);
	ctx->style.option.text_normal = nk_rgb(255,255,255);
	ctx->style.option.active = nk_style_item_color(nk_rgb(255,255,255));
	ctx->style.option.normal = nk_style_item_color(nk_rgb(255,255,255));
	ctx->style.option.hover = nk_style_item_color(nk_rgb(255,255,255));
	nk_style_set_font(ctx, &uiManager->available_fonts["smallMain"]->handle);
}

void InputsMenu::startUI(struct nk_context *ctx, std::map<std::string, nk_font *> fonts)
{
	std::cout << "start UI inputs menu" << std::endl;
}

void InputsMenu::drawInputUI(struct nk_context *ctx, std::string label, InputInfo & inputInfo)
{
	nk_layout_row_push(ctx, (menuWidth - 30 * 2 - 10 * 3) / 2 - 40 * 2);
	nk_label(ctx, label.c_str(), NK_TEXT_CENTERED);
	nk_layout_row_push(ctx, 40);
	// nk_edit_string(ctx, NK_EDIT_SIMPLE, inputInfo.text, &inputInfo.text_len, 2, nk_filter_default);
	auto normalButton = ctx->style.button.normal;
	if (inputInfo.waitingBind)
		ctx->style.button.normal = ctx->style.button.active;
	if (nk_button_label(ctx, inputInfo.text))
	{
		inputInfo.waitingBind = true;
		BeerEngine::Input::onKeyPushed = [label, &inputInfo] (int key) {
			Game::Input::keyBindings[label] = static_cast<BeerEngine::KeyCode>(key);
			inputInfo.text[0] = key;
			inputInfo.waitingBind = false;
			BeerEngine::Input::onKeyPushed = BeerEngine::Input::onKeyPushedDefault();
		};
	}
	if (inputInfo.waitingBind)
		ctx->style.button.normal = normalButton;
}

void InputsMenu::drawInputsUI(struct nk_context *ctx)
{
	nk_layout_row_begin(ctx, NK_STATIC, 50, 4);
	for (auto it = inputsList.begin(); it != inputsList.end(); it++)
		drawInputUI(ctx, *it, inputs[*it]);
}

// not used anymore after input capture method change
void InputsMenu::updateKeyBindings()
{
	std::cout << "key bindings update" << std::endl;
	for (auto it = inputsList.begin(); it != inputsList.end(); it++)
	{
		char c = inputs[*it].text[0];
		if (c >= 97 && c <= 122)
			c -= 32;
		Game::Input::keyBindings[*it] = static_cast<BeerEngine::KeyCode>(c);
		std::cout << "input of " << *it << " is now " << Game::Input::keyBindings[*it] << std::endl;
	}
}

void InputsMenu::renderUI(struct nk_context *ctx)
{
	uiManager->setThemeUI(ctx);
	setUI(ctx);
	menuWidth = 640;
	menuHeight = 350 + 5 * 10;
	float xOffset = 150;
	float yOffset = 50;
	auto window_rect = nk_rect(
		WINDOW_WIDTH / 2 - menuWidth / 2 + xOffset, 
		WINDOW_HEIGHT / 2 - menuHeight / 2 + yOffset, 
		menuWidth, 
		menuHeight
	);
	if (nk_begin(ctx, "Inputs", window_rect, 0))
	{
		drawInputsUI(ctx);
	}
	nk_end(ctx);

	// window of the back button
	uiManager->setThemeUI(ctx);
	ctx->style.window.fixed_background = nk_style_item_hide();
	ctx->style.window.spacing = nk_vec2(0, 0);
	ctx->style.window.padding = nk_vec2(0, 0);
	menuWidth = 320;
	menuHeight = 75;
	xOffset = 150;
	yOffset = 275;
	window_rect = nk_rect(
		WINDOW_WIDTH / 2 - menuWidth / 2 + xOffset, 
		WINDOW_HEIGHT / 2 - menuHeight / 2 + yOffset, 
		menuWidth, 
		menuHeight
	);
	if (nk_begin(ctx, "Inputs back", window_rect, NK_WINDOW_NO_SCROLLBAR))
	{
		nk_layout_row_dynamic(ctx, 75, 1);

		if (nk_button_label(ctx, "Back"))
		{
			// updateKeyBindings();
			this->setActive(false);
			settingsMenu->setActive(true);
		}
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
