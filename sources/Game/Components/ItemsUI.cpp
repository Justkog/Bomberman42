#include "Game/Components/ItemsUI.hpp"
#include "Core/Window.hpp"
#include "Game/Components/UIThemeManager.hpp"
#include "Game/Components/Player.hpp"
#include "Game/Components/Character.hpp"
#include "Game/Components/Breakable.hpp"

namespace Game
{
	namespace Component
	{
// STATIC ########################################################

// ###############################################################

// CANONICAL #####################################################

ItemsUI::ItemsUI ( void )
{
	return ;
}

ItemsUI::ItemsUI ( ItemsUI const & src )
{
	*this = src;
	return ;
}

ItemsUI &				ItemsUI::operator=( ItemsUI const & rhs )
{
	(void) rhs;
	if (this != &rhs)
	{}
	return (*this);
}

ItemsUI::~ItemsUI ( void )
{
	return ;
}

// ###############################################################

// CONSTRUCTOR POLYMORPHISM ######################################

ItemsUI::ItemsUI(BeerEngine::GameObject *gameObject) :
Component(gameObject),
player(nullptr)
{
	
}

// ###############################################################

// OVERLOAD OPERATOR #############################################

std::ostream &				operator<<(std::ostream & o, ItemsUI const & i)
{
	(void)i;
	return (o);
}

// ###############################################################

// PUBLIC METHOD #################################################

void ItemsUI::acknowledgePlayerDeath(glm::vec3 pos, int value)
{
	(void) pos;
	(void) value;
	player = NULL;
}

void ItemsUI::start()
{
	// std::cout << "ItemsUI start" << std::endl;
	shoeImage = uiManager->loadSprite("assets/textures/shoe.png");
	bombImage = uiManager->loadSprite("assets/textures/bomb.png");
	rangeImage = uiManager->loadSprite("assets/textures/range.png");
	player = _gameObject->_scene.find("player")->GetComponent<Player>();
	auto playerBreakable = _gameObject->_scene.find("player")->GetComponent<Breakable>();
	playerBreakable->onDestruction.bind(&ItemsUI::acknowledgePlayerDeath, this);
}

void ItemsUI::startUI(struct nk_context *ctx, std::map<std::string, nk_font *> fonts)
{
	(void) ctx;
	(void) fonts;
}

void ItemsUI::setUI(struct nk_context *ctx)
{
	ctx->style.text.color = nk_rgb(255,255,255);
}

void ItemsUI::drawItemInfo(struct nk_context *ctx, nk_style_item image, int itemInfo)
{
	float rowHeight = 75;
	float imageSpaceWidth = 150;
	float targetRatio = imageSpaceWidth / rowHeight;
	float imageRatio = static_cast<float>(image.data.image.w) / static_cast<float>(image.data.image.h);

	if (imageRatio < targetRatio)
	{
		// image height remains rowHeight
		// need to recalculate imageWidth to make it the width of the center column
		float imageWidth = rowHeight * imageRatio;

		nk_layout_row_begin(ctx, NK_STATIC, rowHeight, 4);

		// left column to center image
		nk_layout_row_push(ctx, (imageSpaceWidth - imageWidth) / 2);
		ctx->style.window.fixed_background = nk_style_item_hide();
		if (nk_group_begin(ctx, "column1", NK_WINDOW_NO_SCROLLBAR | NK_WINDOW_NOT_INTERACTIVE)) { // column 1
			nk_group_end(ctx);
		}

		// column containing image
		nk_layout_row_push(ctx, imageWidth);
		ctx->style.window.fixed_background = image;
		if (nk_group_begin(ctx, "column1", NK_WINDOW_NO_SCROLLBAR | NK_WINDOW_NOT_INTERACTIVE)) { // column 1
			nk_group_end(ctx);
		}

		// right column to center image
		nk_layout_row_push(ctx, (imageSpaceWidth - imageWidth) / 2);
		ctx->style.window.fixed_background = nk_style_item_hide();
		if (nk_group_begin(ctx, "column1", NK_WINDOW_NO_SCROLLBAR | NK_WINDOW_NOT_INTERACTIVE)) { // column 1
			nk_group_end(ctx);
		}

		// last column to display item info
		std::stringstream ssInfo;
		ssInfo << itemInfo;
		nk_label(ctx, ssInfo.str().c_str(), NK_TEXT_LEFT);
	}
}

void ItemsUI::update()
{
	if (player)
	{
		speed = player->_character->_speed * 4;
		bombs = player->_character->_bombNb;
		range = player->_character->_explosionSize;
	}
	else
	{
		speed = 0;
		bombs = 0;
		range = 0;
	}
}

void ItemsUI::fixedUpdate() {}

void ItemsUI::renderUI(struct nk_context *ctx)
{
	uiManager->setThemeUI(ctx);
	setUI(ctx);
	float panelWidth = 225;
	float panelHeight = 400;
	// float xOffset = 0;
	float yOffset = 0;
	auto window_rect = nk_rect(
		BeerEngine::Window::GetInstance()->getWidth() - panelWidth, 
		yOffset, 
		panelWidth, 
		panelHeight
	);
	if (nk_begin(ctx, "Items", window_rect, NK_WINDOW_NO_SCROLLBAR | NK_WINDOW_NOT_INTERACTIVE | NK_WINDOW_BACKGROUND))
	{
		drawItemInfo(ctx, shoeImage, speed);
		drawItemInfo(ctx, bombImage, bombs);
		drawItemInfo(ctx, rangeImage, range);
	}
	nk_end(ctx);
	uiManager->resetToDefaultUI(ctx);
}

nlohmann::json	ItemsUI::serialize()
{
	auto j = Component::serialize();
	j.merge_patch({
		{"componentClass", type},
		{"uiManager", SERIALIZE_BY_ID(uiManager)},
		{"player", SERIALIZE_BY_ID(player)},
	});
	return j;
}

void ItemsUI::deserialize(const nlohmann::json & j, BeerEngine::JsonLoader & loader)
{
	Component::deserialize(j, loader);
	DESERIALIZE_BY_ID(this->uiManager, UIThemeManager, "uiManager", loader);
	DESERIALIZE_BY_ID(this->player, Player, "player", loader);
}

REGISTER_COMPONENT_CPP(ItemsUI)

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
