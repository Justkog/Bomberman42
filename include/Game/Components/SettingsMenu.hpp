// ------------------------------------------------------------	//
//																//
//																//
// ------------------------------------------------------------	//

#ifndef SETTINGSMENU_HPP
# define SETTINGSMENU_HPP

/*!
 * \file SettingsMenu.hpp
 * \brief Menu de gestion des settings.
 * \author jblondea
 */

#include "Core/Core.hpp"
#include "Core/Component/Component.hpp"
#include "Core/Component/IStart.hpp"
#include "Core/Component/IUpdate.hpp"
#include "Core/Component/IUI.hpp"
#include "Core/Component/IStartUI.hpp"

namespace Game
{
	namespace Component
	{
		class MainMenu;		
		class InputsMenu;		
		class UIThemeManager;
		class Settings;

		enum {FULL_SCREEN, WINDOWED};


		class SettingsMenu : public BeerEngine::Component::Component, 
								public BeerEngine::Component::IStart,
								public BeerEngine::Component::IStartUI,
								public BeerEngine::Component::IUI
		{
		private:
			bool			settingsReset;
			int				mousePreviousStatus;
			float			targetHeight;
			float			targetWidth;
		
		public:
			float			musicVolume;
			float			soundVolume;
			int				mode;

			MainMenu		*mainMenu;
			InputsMenu		*inputsMenu;
			UIThemeManager	*uiManager;
			Settings		*settingsManager;

			nk_style_window mWindow;

			// SettingsMenu( void );
			// SettingsMenu( SettingsMenu const & src );
			SettingsMenu(BeerEngine::GameObject *gameObject);

			virtual ~SettingsMenu( void );

			SettingsMenu & operator=( SettingsMenu const & rhs );
			friend std::ostream & operator<<(std::ostream & o, SettingsMenu const & i);

			virtual void start();
			virtual void startUI(struct nk_context *ctx, std::map<std::string, nk_font *> fonts);
			virtual void renderUI(struct nk_context *ctx);

			void setUI(struct nk_context *ctx);
			void saveSettings();
			void resetSettings();

			void updateScreenResolution();

	
			REGISTER_COMPONENT_HPP
		};

	};

};

#endif
