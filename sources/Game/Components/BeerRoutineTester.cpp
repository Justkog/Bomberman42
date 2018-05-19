#include "Game/Components/BeerRoutineTester.hpp"
#include "Core/BeerRoutine/BeerRoutine.hpp"
#include "Core/BeerRoutine/ARoutineRunner.hpp"
#include "Core/Input.hpp"

namespace Game
{
	namespace Component
	{
// STATIC ########################################################

// ###############################################################

// CANONICAL #####################################################

BeerRoutineTester::BeerRoutineTester ( void )
{
	return ;
}

BeerRoutineTester::BeerRoutineTester ( BeerRoutineTester const & src )
{
	*this = src;
	return ;
}

BeerRoutineTester &				BeerRoutineTester::operator=( BeerRoutineTester const & rhs )
{
	if (this != &rhs)
	{
		// make stuff
	}
	return (*this);
}

BeerRoutineTester::~BeerRoutineTester ( void )
{
	return ;
}

// ###############################################################

// CONSTRUCTOR POLYMORPHISM ######################################

BeerRoutineTester::BeerRoutineTester(BeerEngine::GameObject *gameObject) :
Component(gameObject)
{

}

// ###############################################################

// OVERLOAD OPERATOR #############################################

std::ostream &				operator<<(std::ostream & o, BeerRoutineTester const & i)
{
	(void)i;
	return (o);
}

// ###############################################################

// PUBLIC METHOD #################################################

void	BeerRoutineTester::testDisplay(std::string content)
{
	std::cout << content << "\n";
}

BeerEngine::BeerRoutine::BeerRoutine *BeerRoutineTester::createTestRoutine()
{
	auto routine = &BeerEngine::BeerRoutine::BeerRoutine::CreateRoutine()
	.addAction([&] () {
		this->testDisplay("first display");
		return true;
	})
	.addTimer(2.0f)
	.addAction([&] () {
		this->testDisplay("late display");
		return true;
	})
	.loop()
	;
	return routine;
}

void BeerRoutineTester::start()
{
	std::cout << "BeerRoutineTester start" << std::endl;
}

void BeerRoutineTester::update()
{
	ARoutineRunner::update();
	// if (BeerEngine::Input::GetKeyDown(BeerEngine::KeyCode::R))
	// 	startRoutine(*createTestRoutine());
	// if (BeerEngine::Input::GetKeyDown(BeerEngine::KeyCode::T))
	// 	stopRoutine(getRunningRoutines()[0]);
}

void BeerRoutineTester::fixedUpdate()
{
	
}

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
