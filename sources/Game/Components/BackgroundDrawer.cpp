#include "Game/Components/BackgroundDrawer.hpp"
#include "Game/Components/UIThemeManager.hpp"
#include "Core/Graphics/Texture.hpp"
#include "Core/Window.hpp"
#include "Game/Assets.hpp"

namespace Game
{
	namespace Component
	{
// STATIC ########################################################

// ###############################################################

// CANONICAL #####################################################

/*BackgroundDrawer::BackgroundDrawer ( void )
{
	return ;
}*/

/*BackgroundDrawer::BackgroundDrawer ( BackgroundDrawer const & src )
{
	*this = src;
	return ;
}*/

BackgroundDrawer &				BackgroundDrawer::operator=( BackgroundDrawer const & rhs )
{
	if (this != &rhs)
	{
		// make stuff
	}
	return (*this);
}

BackgroundDrawer::~BackgroundDrawer ( void )
{
	return ;
}

// ###############################################################

// CONSTRUCTOR POLYMORPHISM ######################################

BackgroundDrawer::BackgroundDrawer(BeerEngine::GameObject *gameObject) :
Component(gameObject)
{
	
}

// ###############################################################

// OVERLOAD OPERATOR #############################################

std::ostream &				operator<<(std::ostream & o, BackgroundDrawer const & i)
{
	(void)i;
	return (o);
}

// ###############################################################

// PUBLIC METHOD #################################################

void BackgroundDrawer::start()
{
	std::cout << "BackgroundDrawer start" << std::endl;
}

void BackgroundDrawer::startUI(struct nk_context *ctx, std::map<std::string, nk_font *> fonts)
{
	std::cout << "start UI background drawer" << std::endl;
}

void BackgroundDrawer::renderUI(struct nk_context *ctx)
{
	ctx->style.window.fixed_background = uiManager->loadSprite("assets/textures/MainScreen.png");
	auto back_window_rect = nk_rect(
		0, 
		0, 
		BeerEngine::Window::GetInstance()->getWidth(), 
		BeerEngine::Window::GetInstance()->getHeight()
	);

	if (nk_begin(ctx, "Background", back_window_rect, NK_WINDOW_NO_SCROLLBAR | NK_WINDOW_NOT_INTERACTIVE | NK_WINDOW_BACKGROUND))
	{
		// just the background image
	}
	nk_end(ctx);
	uiManager->resetToDefaultUI(ctx);
}

nlohmann::json	BackgroundDrawer::serialize()
{
	auto j = Component::serialize();
	j.merge_patch({
		{"componentClass", type},
		{"uiManager", uiManager->_serializationID},
	});
	return j;
}

void BackgroundDrawer::deserialize(const nlohmann::json & j)
{
	Component::deserialize(j);
	DESERIALIZE_BY_ID(this->uiManager, UIThemeManager, "uiManager");
}

REGISTER_COMPONENT_CPP(BackgroundDrawer)

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
