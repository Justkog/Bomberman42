#define NK_INCLUDE_FONT_BAKING
#include "Game/Components/UIThemeManager.hpp"
#include "Core/Graphics/Texture.hpp"
#include "Game/Assets.hpp"

namespace Game
{
	namespace Component
	{
// STATIC ########################################################

// ###############################################################

// CANONICAL #####################################################

/*UIThemeManager::UIThemeManager ( void )
{
	return ;
}*/

/*UIThemeManager::UIThemeManager ( UIThemeManager const & src )
{
	*this = src;
	return ;
}*/

UIThemeManager &				UIThemeManager::operator=( UIThemeManager const & rhs )
{
	if (this != &rhs)
	{
		// make stuff
	}
	return (*this);
}

UIThemeManager::~UIThemeManager ( void )
{
	return ;
}

// ###############################################################

// CONSTRUCTOR POLYMORPHISM ######################################

UIThemeManager::UIThemeManager(BeerEngine::GameObject *gameObject) :
Component(gameObject)
{
	
}

// ###############################################################

// OVERLOAD OPERATOR #############################################

std::ostream &				operator<<(std::ostream & o, UIThemeManager const & i)
{
	(void)i;
	return (o);
}

// ###############################################################

// PUBLIC METHOD #################################################

void UIThemeManager::start()
{
	std::cout << "UIThemeManager start" << std::endl;
}

void UIThemeManager::saveDefaultUI(struct nk_context *ctx)
{
	defaultWindow = ctx->style.window;
	defaultButton = ctx->style.button;
	defaultProperty = ctx->style.property;
	defaultText = ctx->style.text;
	defaultSlider = ctx->style.slider;
}

void UIThemeManager::resetToDefaultUI(struct nk_context *ctx)
{
	ctx->style.window = defaultWindow;
	ctx->style.button = defaultButton;
	ctx->style.property = defaultProperty;
	ctx->style.text = defaultText;
	ctx->style.slider = defaultSlider;
	nk_style_set_font(ctx, &available_fonts["default"]->handle);
}

void UIThemeManager::startUI(struct nk_context *ctx, std::map<std::string, nk_font *> fonts)
{
	std::cout << "start UI theme manager" << std::endl;
	saveDefaultUI(ctx);
	available_fonts = fonts;

	themeButton = defaultButton;
	themeButton.normal = loadSprite("assets/textures/button_normal.png");
	themeButton.text_normal = nk_rgb(0,0,0);
	themeButton.hover = loadSprite("assets/textures/button_hover.png");
	themeButton.text_hover = nk_rgb(0,0,0);
	themeButton.active = loadSprite("assets/textures/button_active.png");
	themeButton.text_active = nk_rgb(0,0,0);
}

void UIThemeManager::renderUI(struct nk_context *ctx)
{

}


nk_style_item UIThemeManager::loadSprite(std::string spritePath)
{
	auto texture = Assets::GetTexture(spritePath);
	auto nk_image = nk_subimage_id(
		texture->getID(), 
		texture->getWidth(),
		texture->getHeight(), 
		nk_rect(0,0,texture->getWidth(),texture->getHeight()));
	return (nk_style_item_image(nk_image));
}

void UIThemeManager::setThemeUI(struct nk_context *ctx)
{
	ctx->style.button = themeButton;
	ctx->style.window.fixed_background = nk_style_item_hide();
	// ctx->style.window.spacing = nk_vec2(0, 10);
	nk_style_set_font(ctx, &available_fonts["main"]->handle);
}

nlohmann::json	UIThemeManager::serialize()
{
	auto j = Component::serialize();
	j.merge_patch({
		{"componentClass", type},
	});
	return j;
}

void UIThemeManager::deserialize(const nlohmann::json & j, BeerEngine::JsonLoader & loader)
{
	Component::deserialize(j, loader);
}

REGISTER_COMPONENT_CPP(UIThemeManager)

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
