#define NK_INCLUDE_FONT_BAKING
#include "Game/Components/Message.hpp"
#include "Game/Components/UIThemeManager.hpp"
#include "Core/Window.hpp"

namespace Game
{
	namespace Component
	{
// STATIC ########################################################

// ###############################################################

// CANONICAL #####################################################

/*Message::Message ( void )
{
	return ;
}*/

/*Message::Message ( Message const & src )
{
	*this = src;
	return ;
}*/

Message &				Message::operator=( Message const & rhs )
{
	if (this != &rhs)
	{
		// make stuff
	}
	return (*this);
}

Message::~Message ( void )
{
	return ;
}

// ###############################################################

// CONSTRUCTOR POLYMORPHISM ######################################

Message::Message(BeerEngine::GameObject *gameObject) :
Component(gameObject),
uiManager(nullptr)
{
	
}

// ###############################################################

// OVERLOAD OPERATOR #############################################

std::ostream &				operator<<(std::ostream & o, Message const & i)
{
	(void)i;
	return (o);
}

// ###############################################################

// PUBLIC METHOD #################################################

void Message::buildLines(std::string text)
{
	std::istringstream iss(text);
 
	std::vector<std::string> words;
    while (iss) {
        std::string word;
        iss >> word;
		words.push_back(word);
    }
	int lettersByLine = 40;

	int lineLetters = 0;
	lines.clear();
	lines.push_back("");
	
	for (auto it = words.begin(); it != words.end(); it++)
	{
		int currentline = lines.size() - 1;
		if (lines[currentline].size() + (*it).size() <= lettersByLine)
		{
			// Add word to current line
			if (lines[currentline].size() != 0)
				lines[currentline] += " ";
			lines[currentline] += *it;
		}
		else
		{
			// Start next line
			lines.push_back(*it);
		}
	}
}

void Message::updateDisplay(std::string text)
{
	std::cout << "update message display" << std::endl;
	buildLines(text);

	// for (auto it = lines.begin(); it != lines.end(); it++)
	// {
	// 	std::cout << *it << std::endl;
	// }
}

void Message::start()
{
	std::cout << "Message start" << std::endl;
	// display("Test Message Test Message Test Message Test Message Test Message Test Message");
}

void Message::startUI(struct nk_context *ctx, std::map<std::string, nk_font *> fonts)
{
	backGround = uiManager->loadSprite("assets/textures/inputsBackground.png");
}

void Message::renderUI(struct nk_context *ctx)
{
	uiManager->setThemeUI(ctx);
	nk_style_set_font(ctx, &uiManager->available_fonts["main"]->handle);
	ctx->style.text.color = nk_rgb(255, 255, 255);
	ctx->style.window.fixed_background = backGround;
	ctx->style.window.padding.y = 15;

	float panelWidth = BeerEngine::Window::GetInstance()->getWidth() * 0.8;
	float panelHeight = 50 * lines.size() + 2 * ctx->style.window.padding.y + ctx->style.window.spacing.y * lines.size() + ctx->style.text.padding.y * lines.size();
	float xOffset = 0;
	float yOffset = 0;
	auto window_rect = nk_rect(
		BeerEngine::Window::GetInstance()->getWidth() / 2 - panelWidth / 2 + xOffset, 
		BeerEngine::Window::GetInstance()->getHeight() / 2 - panelHeight / 2 + yOffset, 
		panelWidth,
		panelHeight
	);
	if (nk_begin(ctx, "Message", window_rect, NK_WINDOW_NO_SCROLLBAR | NK_WINDOW_NOT_INTERACTIVE | NK_WINDOW_BACKGROUND))
	{
		nk_layout_row_dynamic(ctx, 50, 1);
		for (auto line = lines.begin(); line != lines.end(); line++)
		{
			nk_label(ctx, (*line).c_str(), NK_TEXT_CENTERED);
		}
	}
	nk_end(ctx);

	uiManager->resetToDefaultUI(ctx);	
}

nlohmann::json	Message::serialize()
{
	auto j = Component::serialize();
	j.merge_patch({
		{"componentClass", type},
	});
	return j;
}

void Message::deserialize(const nlohmann::json & j, BeerEngine::JsonLoader & loader)
{
	Component::deserialize(j, loader);
}

REGISTER_COMPONENT_CPP(Message)

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
