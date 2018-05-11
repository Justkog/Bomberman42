// ------------------------------------------------------------	//
//																//
//																//
// ------------------------------------------------------------	//

#ifndef INPUTSMENU_HPP
# define INPUTSMENU_HPP

#include "Core/Core.hpp"
#include "Core/Component/Component.hpp"
#include "Core/Component/IStart.hpp"
#include "Core/Component/IUI.hpp"
#include "Core/Component/IStartUI.hpp"

namespace Game
{
	namespace Component
	{
		class SettingsMenu;
		class UIThemeManager;

		struct InputInfo
		{
			char text[15];
			int text_len;
			bool waitingBind;
		};

		class InputsMenu : public BeerEngine::Component::Component, 
								public BeerEngine::Component::IStart,
								public BeerEngine::Component::IStartUI,
								public BeerEngine::Component::IUI
		{
		public:

			std::map<std::string, InputInfo> inputs;
			std::vector<std::string> inputsList;

			SettingsMenu	*settingsMenu;
			UIThemeManager	*uiManager;

			float menuWidth;
			float menuHeight;

			// InputsMenu( void );
			// InputsMenu( InputsMenu const & src );
			InputsMenu(BeerEngine::GameObject *gameObject);

			virtual ~InputsMenu( void );

			InputsMenu & operator=( InputsMenu const & rhs );
			friend std::ostream & operator<<(std::ostream & o, InputsMenu const & i);

			virtual void start();
			virtual void startUI(struct nk_context *ctx, std::map<std::string, nk_font *> fonts);
			virtual void renderUI(struct nk_context *ctx);

			void setUI(struct nk_context *ctx);

			void setMapKey(std::string label);
			void drawInputsUI(struct nk_context *ctx);
			void drawInputUI(struct nk_context *ctx, std::string label, InputInfo & inputInfo);
			void updateKeyBindings();
			void updateDisplayedInputKeys();

		};
	};
};

#endif
