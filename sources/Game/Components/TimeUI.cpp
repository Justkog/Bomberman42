#include "Game/Components/TimeUI.hpp"
#include "Game/Components/UIThemeManager.hpp"

namespace Game
{
	namespace Component
	{
// STATIC ########################################################

// ###############################################################

// CANONICAL #####################################################

/*TimeUI::TimeUI ( void )
{
	return ;
}*/

/*TimeUI::TimeUI ( TimeUI const & src )
{
	*this = src;
	return ;
}*/

TimeUI &				TimeUI::operator=( TimeUI const & rhs )
{
	if (this != &rhs)
	{
		// make stuff
	}
	return (*this);
}

TimeUI::~TimeUI ( void )
{
	return ;
}

// ###############################################################

// CONSTRUCTOR POLYMORPHISM ######################################

TimeUI::TimeUI(BeerEngine::GameObject *gameObject) :
Component(gameObject)
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

void TimeUI::start()
{
	std::cout << "TimeUI start" << std::endl;
}

void TimeUI::setUI(struct nk_context *ctx)
{
	// nk_style_set_font(ctx, &uiManager->available_fonts["smallMain"]->handle);
}

void TimeUI::startUI(struct nk_context *ctx, std::map<std::string, nk_font *> fonts)
{
	std::cout << "start UI main menu" << std::endl;
}

void TimeUI::renderUI(struct nk_context *ctx)
{
	uiManager->setThemeUI(ctx);
	setUI(ctx);
	// float menuWidth = 320;
	// float menuHeight = 375 + 5 * 10;
	// float xOffset = 0;
	// float yOffset = 100;
	// auto window_rect = nk_rect(
	// 	BeerEngine::Window::GetInstance()->getWidth() / 2 - menuWidth / 2 + xOffset, 
	// 	BeerEngine::Window::GetInstance()->getHeight() / 2 - menuHeight / 2 + yOffset, 
	// 	menuWidth, 
	// 	menuHeight
	// );
	// if (nk_begin(ctx, "Menu", window_rect, NK_WINDOW_NO_SCROLLBAR))
	// {
	// 	nk_layout_row_dynamic(ctx, 75, 1);

	// 	if (nk_button_label(ctx, "Resume"))
	// 		this->setActive(false);
	// 	if (nk_button_label(ctx, "Back to Main Menu"))
	// 		BeerEngine::SceneManager::LoadScene<SceneMain>();
	// }
	// nk_end(ctx);
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
