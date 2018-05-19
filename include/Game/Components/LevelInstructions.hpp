// ------------------------------------------------------------	//
//																//
//																//
// ------------------------------------------------------------	//

#ifndef LEVELINSTRUCTIONS_HPP
# define LEVELINSTRUCTIONS_HPP

#include "Core/Core.hpp"
#include "Game/Game.hpp"
#include "Core/Component/Component.hpp"
#include "Core/Component/IStart.hpp"
#include "Core/Component/IUpdate.hpp"
#include "Core/BeerRoutine/ARoutineRunner.hpp"

namespace Game
{
	namespace Component
	{
		struct GameInstruction
		{
			std::string	message;
			float		delay;
		};

		class LevelInstructions : public BeerEngine::Component::Component, 
									public BeerEngine::Component::IUpdate, 
									public BeerEngine::Component::IStart,
									public BeerEngine::BeerRoutine::ARoutineRunner
		{
		private:
			BeerEngine::BeerRoutine::BeerRoutine *createInstructionsRoutine();
			std::vector<GameInstruction> instructions;

		public:
			Message *message;

			// LevelInstructions( void );
			// LevelInstructions( LevelInstructions const & src );
			LevelInstructions(BeerEngine::GameObject *gameObject);

			virtual ~LevelInstructions( void );

			LevelInstructions & operator=( LevelInstructions const & rhs );
			friend std::ostream & operator<<(std::ostream & o, LevelInstructions const & i);

			virtual void start();
			virtual void update();
			virtual void fixedUpdate();
			
			void startInstructions();
			void setInstructions(std::vector<GameInstruction> instructions);

			REGISTER_COMPONENT_HPP
	
		};

	};

};

#endif
