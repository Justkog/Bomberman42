#define NK_INCLUDE_FONT_BAKING
#include "Game/Components/StartTimerUI.hpp"
#include "Game/Components/UIThemeManager.hpp"
#include "Core/Window.hpp"

namespace Game
{
	namespace Component
	{
// STATIC ########################################################

// ###############################################################

// CANONICAL #####################################################

StartTimerUI::StartTimerUI ( void )
{
	return ;
}

StartTimerUI::StartTimerUI ( StartTimerUI const & src )
{
	*this = src;
	return ;
}

StartTimerUI &				StartTimerUI::operator=( StartTimerUI const & rhs )
{
	(void) rhs;
	if (this != &rhs)
	{}
	return (*this);
}

StartTimerUI::~StartTimerUI ( void )
{
	return ;
}

// ###############################################################

// CONSTRUCTOR POLYMORPHISM ######################################

StartTimerUI::StartTimerUI(BeerEngine::GameObject *gameObject) :
Component(gameObject)
{
	
}

// ###############################################################

// OVERLOAD OPERATOR #############################################

std::ostream &				operator<<(std::ostream & o, StartTimerUI const & i)
{
	(void)i;
	return (o);
}

// ###############################################################

// PUBLIC METHOD #################################################

void StartTimerUI::updateDisplay(std::string text)
{
	// std::cout << "display update " << text << std::endl;
	this->text = text;
}

void StartTimerUI::start()
{
	// std::cout << "StartTimerUI start" << std::endl;
}

void StartTimerUI::startUI(struct nk_context *ctx, std::map<std::string, nk_font *> fonts)
{
	(void) ctx;
	(void) fonts;
}

void StartTimerUI::renderUI(struct nk_context *ctx)
{
	uiManager->setThemeUI(ctx);
	nk_style_set_font(ctx, &uiManager->available_fonts["bigMain"]->handle);
	ctx->style.text.color = nk_rgb(255, 255, 255);

	float panelWidth = 400;
	float panelHeight = 150;
	float xOffset = 0;
	float yOffset = 0;
	auto window_rect = nk_rect(
		BeerEngine::Window::GetInstance()->getWidth() / 2 - panelWidth / 2 + xOffset, 
		BeerEngine::Window::GetInstance()->getHeight() / 2 - panelHeight / 2 + yOffset, 
		panelWidth,
		panelHeight
	);
	if (nk_begin(ctx, "Start Timer", window_rect, NK_WINDOW_NO_SCROLLBAR | NK_WINDOW_NOT_INTERACTIVE | NK_WINDOW_BACKGROUND))
	{
		nk_layout_row_dynamic(ctx, 100, 1);
		nk_label(ctx, text.c_str(), NK_TEXT_CENTERED);
	}
	nk_end(ctx);

	uiManager->resetToDefaultUI(ctx);
}

nlohmann::json	StartTimerUI::serialize()
{
	auto j = Component::serialize();
	j.merge_patch({
		{"componentClass", type},
	});
	return j;
}

void StartTimerUI::deserialize(const nlohmann::json & j, BeerEngine::JsonLoader & loader)
{
	Component::deserialize(j, loader);
}

REGISTER_COMPONENT_CPP(StartTimerUI)

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
