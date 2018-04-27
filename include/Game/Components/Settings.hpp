// ------------------------------------------------------------	//
//																//
//																//
// ------------------------------------------------------------	//

#ifndef SETTINGS_HPP
# define SETTINGS_HPP

#include <nlohmann/json.hpp>
#include "Core/Component/IStart.hpp"
#include "Core/Component/Component.hpp"
#include "Core/IO/FileUtils.hpp"
#include <vector>
#include <iostream>

namespace Game
{	
	class SettingsContainer
	{
		public:

			float soundVolume;
			std::string stringSetting;
			int intSetting;
			std::vector<std::string> listSettings;
	};

	namespace Component	{		
		class Settings : public BeerEngine::Component::Component, public BeerEngine::Component::IStart
		{
		public:

			// Settings( void );
			// Settings( Settings const & src );
			Settings(BeerEngine::GameObject *gameObject);
			virtual ~Settings( void );

			Settings & operator=( Settings const & rhs );
			friend std::ostream & operator<<(std::ostream & o, Settings const & i);

			void loadSettings();
			void saveSettings();
			void start(void);

			std::string filePath;
			Game::SettingsContainer settingsContainer;
		};
	};
};


#endif
