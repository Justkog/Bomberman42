#define NK_INCLUDE_FONT_BAKING
#include "Game/Components/TimeUI.hpp"
#include "Core/Window.hpp"
#include "Core/Time.hpp"
#include "Game/Components/UIThemeManager.hpp"

namespace Game
{
	namespace Component
	{
// STATIC ########################################################

// ###############################################################

// CANONICAL #####################################################

TimeUI::TimeUI ( void )
{
	return ;
}

TimeUI::TimeUI ( TimeUI const & src )
{
	*this = src;
	return ;
}

TimeUI &				TimeUI::operator=( TimeUI const & rhs )
{
	(void) rhs;
	if (this != &rhs)
	{}
	return (*this);
}

TimeUI::~TimeUI ( void )
{
	return ;
}

// ###############################################################

// CONSTRUCTOR POLYMORPHISM ######################################

TimeUI::TimeUI(BeerEngine::GameObject *gameObject) :
Component(gameObject),
_started(false)
{
	
}

// ###############################################################

// OVERLOAD OPERATOR #############################################

std::ostream &				operator<<(std::ostream & o, TimeUI const & i)
{
	(void)i;
	return (o);
}

// ###############################################################

// PUBLIC METHOD #################################################

void TimeUI::startClock()
{
	_startTimeSinceStartup = BeerEngine::Time::GetTimeSinceStartup();
	_started = true;
}

void TimeUI::start()
{
	std::cout << "TimeUI start" << std::endl;
	backGround = uiManager->loadSprite("assets/textures/stone_panel.png");
	// tvScreen = uiManager->loadSprite("assets/textures/timetvscreen.png");
	timeSinceGameStart = 0;
}

void TimeUI::setUI(struct nk_context *ctx)
{
	nk_style_set_font(ctx, &uiManager->available_fonts["secondary"]->handle);
	ctx->style.text.color = nk_rgb(0, 0, 0);
}

void TimeUI::startUI(struct nk_context *ctx, std::map<std::string, nk_font *> fonts)
{
	std::cout << "start UI TimeUI" << std::endl;
}

std::string	formatTime(double time)
{
	std::stringstream ssTime;
	if (static_cast<int>(time / 60) < 10)
		ssTime << 0;
	ssTime << static_cast<int>(time / 60) << ":";
	if (static_cast<int>(time) % 60 < 10)
		ssTime << 0;
	ssTime << static_cast<int>(time) % 60;
	return ssTime.str();
}

void TimeUI::renderUI(struct nk_context *ctx)
{
	uiManager->setThemeUI(ctx);
	setUI(ctx);
	float ratio = 604.0f / 910.0f;
	float panelWidth = 400;
	float panelHeight = panelWidth * ratio;
	float xOffset = 0;
	float yOffset = -125;
	auto window_rect = nk_rect(
		BeerEngine::Window::GetInstance()->getWidth() / 2 - panelWidth / 2 + xOffset, 
		yOffset, 
		panelWidth, 
		panelHeight
	);
	ctx->style.window.fixed_background = backGround;
	if (nk_begin(ctx, "Time", window_rect, NK_WINDOW_NO_SCROLLBAR | NK_WINDOW_NOT_INTERACTIVE | NK_WINDOW_BACKGROUND))
	{
		nk_layout_row_dynamic(ctx, 100, 1);
		nk_layout_row_begin(ctx, NK_STATIC, 125, 2);

		// // empty column to center buttons
		nk_layout_row_push(ctx, 75);
		ctx->style.window.fixed_background = nk_style_item_hide();
		if (nk_group_begin(ctx, "column1", NK_WINDOW_NO_SCROLLBAR | NK_WINDOW_NOT_INTERACTIVE)) { // column 1
			nk_group_end(ctx);
		}
		nk_layout_row_push(ctx, 250);

		timeSinceGameStart = 0;
		if (_started)
			timeSinceGameStart = BeerEngine::Time::GetTimeSinceStartup() - _startTimeSinceStartup;
		auto time = formatTime(timeSinceGameStart);
		nk_label(ctx, time.c_str(), NK_TEXT_CENTERED);
	}
	nk_end(ctx);
	// ctx->style.window.fixed_background = tvScreen;
	// if (nk_begin(ctx, "TimeTVScreen", window_rect, NK_WINDOW_NO_SCROLLBAR | NK_WINDOW_NOT_INTERACTIVE | NK_WINDOW_BACKGROUND))
	// {
	// 	// nk_layout_row_dynamic(ctx, 75, 1);
	// }
	// nk_end(ctx);
	uiManager->resetToDefaultUI(ctx);
}

nlohmann::json	TimeUI::serialize()
{
	auto j = Component::serialize();
	j.merge_patch({
		{"componentClass", type},
		{"uiManager", SERIALIZE_BY_ID(uiManager)},
	});
	return j;
}

void TimeUI::deserialize(const nlohmann::json & j, BeerEngine::JsonLoader & loader)
{
	Component::deserialize(j, loader);
	DESERIALIZE_BY_ID(this->uiManager, UIThemeManager, "uiManager", loader);
}

REGISTER_COMPONENT_CPP(TimeUI)

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
