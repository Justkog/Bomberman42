#include "Game/Components/BeerRoutineTester.hpp"
#include "Core/BeerRoutine/BeerRoutine.hpp"
#include "Core/Input.hpp"

namespace Game
{
	namespace Component
	{
// STATIC ########################################################

// ###############################################################

// CANONICAL #####################################################

/*BeerRoutineTester::BeerRoutineTester ( void )
{
	return ;
}*/

/*BeerRoutineTester::BeerRoutineTester ( BeerRoutineTester const & src )
{
	*this = src;
	return ;
}*/

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
	.addTimer(1.0f)
	.addAction([&] () {
		this->testDisplay("late display");
		return true;
	})
	;
	return routine;
}

void BeerRoutineTester::start()
{
	std::cout << "BeerRoutineTester start" << std::endl;
	
	testRoutine = createTestRoutine();
}

void BeerRoutineTester::update()
{
	if (BeerEngine::Input::GetKeyDown(BeerEngine::KeyCode::R))
		startRoutine(*testRoutine);
	if (currentRoutine)
	{
		currentRoutine->update();
	}
}

void BeerRoutineTester::fixedUpdate()
{
	
}

void BeerRoutineTester::startRoutine(BeerEngine::BeerRoutine::BeerRoutine &routine)
{
	std::cout << "starting routine!" << "\n";
	if (currentRoutine)
	{
		std::cout << "need to stop old routine!" << "\n";
	}
	currentRoutine = &routine;
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
