#include "Game/Components/LevelInstructions.hpp"
#include "Game/Components/Message.hpp"
#include "Core/BeerRoutine/BeerRoutine.hpp"

namespace Game
{
	namespace Component
	{
// STATIC ########################################################

// ###############################################################

// CANONICAL #####################################################

/*LevelInstructions::LevelInstructions ( void )
{
	return ;
}*/

/*LevelInstructions::LevelInstructions ( LevelInstructions const & src )
{
	*this = src;
	return ;
}*/

LevelInstructions &				LevelInstructions::operator=( LevelInstructions const & rhs )
{
	if (this != &rhs)
	{
		// make stuff
	}
	return (*this);
}

LevelInstructions::~LevelInstructions ( void )
{
	return ;
}

// ###############################################################

// CONSTRUCTOR POLYMORPHISM ######################################

LevelInstructions::LevelInstructions(BeerEngine::GameObject *gameObject) :
Component(gameObject)
{
	
}

// ###############################################################

// OVERLOAD OPERATOR #############################################

std::ostream &				operator<<(std::ostream & o, LevelInstructions const & i)
{
	(void)i;
	return (o);
}

// ###############################################################

// PUBLIC METHOD #################################################

void LevelInstructions::startInstructions()
{
	std::cout << "starting instructions" << std::endl;
	this->message->setActive(true);
	startRoutine(*createInstructionsRoutine());
}

void LevelInstructions::setInstructions(std::vector<GameInstruction> instructions)
{
	this->instructions = instructions;	
}

void LevelInstructions::start()
{
	std::cout << "LevelInstructions start" << std::endl;
}

void LevelInstructions::update()
{
	BeerEngine::BeerRoutine::ARoutineRunner::update();
}

void LevelInstructions::fixedUpdate()
{
	
}

nlohmann::json	LevelInstructions::serialize()
{
	auto j = Component::serialize();
	j.merge_patch({
		{"componentClass", type},
	});
	return j;
}

void LevelInstructions::deserialize(const nlohmann::json & j, BeerEngine::JsonLoader & loader)
{
	Component::deserialize(j, loader);
}

REGISTER_COMPONENT_CPP(LevelInstructions)

// ###############################################################

// GETTER METHOD #################################################

// ###############################################################

// SETTER METHOD #################################################

// ###############################################################

// PRIVATE METHOD ################################################

BeerEngine::BeerRoutine::BeerRoutine *LevelInstructions::createInstructionsRoutine()
{
	auto routine = &BeerEngine::BeerRoutine::BeerRoutine::CreateRoutine();

	for (auto instr = instructions.begin(); instr != instructions.end(); instr++)
	{
		auto instrMessage = instr->message;
		auto instrDelay = instr->delay;
		routine->addAction([this, instrMessage] () {
			this->message->updateDisplay(instrMessage);
			return true;
		})
		.addTimer(instrDelay);
	}
	routine->addAction([this] () {
		this->message->setActive(false);
		return true;
	});
	return routine;
}

// ###############################################################

// EXCEPTION METHOD ##############################################

// ###############################################################

// EXTERNAL ######################################################

// ###############################################################
	}
}
