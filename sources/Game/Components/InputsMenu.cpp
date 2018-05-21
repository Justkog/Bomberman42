#define NK_INCLUDE_FONT_BAKING
#include "Game/Components/InputsMenu.hpp"
#include "Game/Components/SettingsMenu.hpp"
#include "Game/Components/UIThemeManager.hpp"
#include "Game/Input.hpp"
#include "Core/Input.hpp"
#include "Core/Window.hpp"

namespace Game
{
	namespace Component
	{
// STATIC ########################################################

// ###############################################################

// CANONICAL #####################################################

InputsMenu::InputsMenu ( void )
{
	return ;
}

InputsMenu::InputsMenu ( InputsMenu const & src )
{
	*this = src;
	return ;
}

InputsMenu &				InputsMenu::operator=( InputsMenu const & rhs )
{
	(void) rhs;
	if (this != &rhs)
	{}
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

void fillInputText(InputInfo & input, std::string text)
{
	strcpy(input.text, text.c_str());
	input.text_len = text.size();
}

void keyToText(InputInfo & input, int key)
{
	if (key == ' ')
		fillInputText(input, "space");
	else if (key == static_cast<int>(BeerEngine::KeyCode::LEFT))
		fillInputText(input, "left");
	else if (key == static_cast<int>(BeerEngine::KeyCode::RIGHT))
		fillInputText(input, "right");
	else if (key == static_cast<int>(BeerEngine::KeyCode::UP))
		fillInputText(input, "up");
	else if (key == static_cast<int>(BeerEngine::KeyCode::DOWN))
		fillInputText(input, "down");
	else if (key == static_cast<int>(BeerEngine::KeyCode::KP_0))
		fillInputText(input, "KP 0");
	else if (key == static_cast<int>(BeerEngine::KeyCode::KP_1))
		fillInputText(input, "KP 1");
	else if (key == static_cast<int>(BeerEngine::KeyCode::KP_2))
		fillInputText(input, "KP 2");
	else if (key == static_cast<int>(BeerEngine::KeyCode::KP_3))
		fillInputText(input, "KP 3");
	else if (key == static_cast<int>(BeerEngine::KeyCode::KP_4))
		fillInputText(input, "KP 4");
	else if (key == static_cast<int>(BeerEngine::KeyCode::KP_5))
		fillInputText(input, "KP 5");
	else if (key == static_cast<int>(BeerEngine::KeyCode::KP_6))
		fillInputText(input, "KP 6");
	else if (key == static_cast<int>(BeerEngine::KeyCode::KP_7))
		fillInputText(input, "KP 7");
	else if (key == static_cast<int>(BeerEngine::KeyCode::KP_8))
		fillInputText(input, "KP 8");
	else if (key == static_cast<int>(BeerEngine::KeyCode::KP_9))
		fillInputText(input, "KP 9");
	else
	{
		input.text[0] = key;
		input.text[1] = 0;
		input.text_len = 1;
	}
}

void InputsMenu::setMapKey(std::string label)
{
	keyToText(inputs[label], Game::Input::keyBindings[label]);
	inputs[label].waitingBind = false;
	inputsList.push_back(label);
}

void InputsMenu::updateDisplayedInputKeys()
{
	for (auto it = inputsList.begin(); it != inputsList.end(); it++)
		keyToText(inputs[*it], Game::Input::keyBindings[*it]);
}

void InputsMenu::start()
{
	// std::cout << "InputsMenu start" << std::endl;
	setMapKey("move up");
	setMapKey("move down");
	setMapKey("move left");
	setMapKey("move right");
	setMapKey("bomb");
	setMapKey("change view");
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
	(void) ctx;
	(void) fonts;
	// std::cout << "start UI inputs menu" << std::endl;
}


void InputsMenu::drawInputUI(struct nk_context *ctx, std::string label, InputInfo & inputInfo, InputInfo * prevInput)
{
	float labelWidth = (menuWidth - 30 * 2 - 10 * 3) / 2 - 40 * 2;
	float buttonWidth = 40;
	if (inputInfo.text_len == 1 && (!prevInput || prevInput->text_len != 1))
	{
		nk_layout_row_begin(ctx, NK_STATIC, 50, 4);
	}
	else if(inputInfo.text_len != 1)
	{
		buttonWidth = 200;
		nk_layout_row_begin(ctx, NK_STATIC, 50, 2);
	}
	// nk_layout_row_push(ctx, (menuWidth - 30 * 2 - 10 * 3) / 2 - 40 * 2);
	nk_layout_row_push(ctx, labelWidth);
	nk_label(ctx, label.c_str(), NK_TEXT_CENTERED);
	// nk_layout_row_push(ctx, 40);
	nk_layout_row_push(ctx, buttonWidth);
	// nk_edit_string(ctx, NK_EDIT_SIMPLE, inputInfo.text, &inputInfo.text_len, 2, nk_filter_default);
	auto normalButton = ctx->style.button.normal;
	if (inputInfo.waitingBind)
		ctx->style.button.normal = ctx->style.button.active;
	if (nk_button_label(ctx, inputInfo.text))
	{
		for (auto it = inputsList.begin(); it != inputsList.end(); it++)
			inputs[*it].waitingBind = false;
		inputInfo.waitingBind = true;
		BeerEngine::Input::onKeyPushed = [label, &inputInfo] (int key) {
			Game::Input::keyBindings[label] = static_cast<BeerEngine::KeyCode>(key);
			keyToText(inputInfo, key);
			inputInfo.waitingBind = false;
			BeerEngine::Input::onKeyPushed = BeerEngine::Input::onKeyPushedDefault();
		};
	}
	if (inputInfo.waitingBind)
		ctx->style.button.normal = normalButton;
}

void InputsMenu::drawInputsUI(struct nk_context *ctx)
{
	for (auto it = inputsList.begin(); it != inputsList.end(); it++)
		drawInputUI(ctx, *it, inputs[*it], it == inputsList.begin() ? NULL : &inputs[*(it - 1)]);
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
		BeerEngine::Window::GetInstance()->getWidth() / 2 - menuWidth / 2 + xOffset, 
		BeerEngine::Window::GetInstance()->getHeight() / 2 - menuHeight / 2 + yOffset, 
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
		BeerEngine::Window::GetInstance()->getWidth() / 2 - menuWidth / 2 + xOffset, 
		BeerEngine::Window::GetInstance()->getHeight() / 2 - menuHeight / 2 + yOffset, 
		menuWidth, 
		menuHeight
	);
	if (nk_begin(ctx, "Inputs back", window_rect, NK_WINDOW_NO_SCROLLBAR))
	{
		nk_layout_row_dynamic(ctx, 75, 1);

		if (nk_button_label(ctx, "Back") || BeerEngine::Input::GetKeyDown(BeerEngine::KeyCode::ESCAPE))
		{
			// updateKeyBindings();
			this->setActive(false);
			settingsMenu->setActive(true);
		}
	}
	nk_end(ctx);
	uiManager->resetToDefaultUI(ctx);
}

nlohmann::json	InputsMenu::serialize()
{
	auto j = Component::serialize();
	j.merge_patch({
		{"componentClass", type},
		{"settingsMenu", SERIALIZE_BY_ID(settingsMenu)},
		{"uiManager", SERIALIZE_BY_ID(uiManager)},
	});
	return j;
}

void InputsMenu::deserialize(const nlohmann::json & j, BeerEngine::JsonLoader & loader)
{
	Component::deserialize(j, loader);
	DESERIALIZE_BY_ID(this->settingsMenu, SettingsMenu, "settingsMenu", loader);
	DESERIALIZE_BY_ID(this->uiManager, UIThemeManager, "uiManager", loader);
}

REGISTER_COMPONENT_CPP(InputsMenu)

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
