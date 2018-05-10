// ------------------------------------------------------------	//
//																//
//																//
// ------------------------------------------------------------	//

#ifndef SETTINGS_HPP
# define SETTINGS_HPP

#include "Core/Core.hpp"
#include "Core/Component/IStart.hpp"
#include "Core/Component/Component.hpp"

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

			void loadSettings();
			void saveSettings();
			void start(void);

			nlohmann::json	serialize();
			virtual void deserialize(const nlohmann::json & j);

			REGISTER_COMPONENT_HPP

			std::string filePath;
			Game::SettingsContainer settingsContainer;
		};
	};
};

std::ostream & operator<<(std::ostream & o, Game::Component::Settings const & i);

#endif
