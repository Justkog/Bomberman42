// ------------------------------------------------------------	//
//																//
//																//
// ------------------------------------------------------------	//

#ifndef GAME_INPUT_HPP
# define GAME_INPUT_HPP

/*!
 * \file Input.hpp
 * \brief Mise en relation des inputs de jeu avec les inputs de l'engine.
 * \author jblondea
 */

#include "Core/Core.hpp"
#include "Core/KeyCode.hpp"

namespace Game
{
	class Input
	{
	public:
		static std::map<std::string, BeerEngine::KeyCode>	keyBindings;

		Input( void );
		Input( Input const & src );

		virtual ~Input( void );

		Input & operator=( Input const & rhs );
		friend std::ostream & operator<<(std::ostream & o, Input const & i);
	};
};

#endif
