// ------------------------------------------------------------	//
//																//
//																//
// ------------------------------------------------------------	//

#ifndef SETTINGS_HPP
# define SETTINGS_HPP

#include <nlohmann/json.hpp>
#include "Core/Component/IStart.hpp"

namespace Game
{	
	namespace Component	{		
		class Settings : public BeerEngine::Component::IStart
		{
		public:

			Settings( void );
			Settings( Settings const & src );
			virtual ~Settings( void );

			Settings & operator=( Settings const & rhs );
			friend std::ostream & operator<<(std::ostream & o, Settings const & i);

			void loadSettings();
		};

	};

};

#endif
