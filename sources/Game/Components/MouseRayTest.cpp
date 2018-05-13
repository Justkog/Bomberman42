#include "Game/Components/MouseRayTest.hpp"
#include "Core/Input.hpp"
#include "Core/Window.hpp"
#include "Core/Camera.hpp"
#include "Core/Graphics/MeshBuilder.hpp"
#include "Core/Graphics/Graphics.hpp"
#include "Core/Graphics/Mesh.hpp"
#include "Core/Component/MeshRenderer.hpp"
#include "Core/Component/RaysRenderer.hpp"
#include "Core/IO/FileUtils.hpp"
#include "Core/Graphics/AMaterial.hpp"
#include "Core/Physics/Physics.hpp"
#include "Core/Component/ACollider.hpp"
#include "Core/GameObject.hpp"

namespace Game
{
	namespace Component
	{
// STATIC ########################################################

// ###############################################################

// CANONICAL #####################################################

/*MouseRayTest::MouseRayTest ( void )
{
	return ;
}*/

/*MouseRayTest::MouseRayTest ( MouseRayTest const & src )
{
	*this = src;
	return ;
}*/

MouseRayTest &				MouseRayTest::operator=( MouseRayTest const & rhs )
{
	if (this != &rhs)
	{
		// make stuff
	}
	return (*this);
}

MouseRayTest::~MouseRayTest ( void )
{
	return ;
}

// ###############################################################

// CONSTRUCTOR POLYMORPHISM ######################################

MouseRayTest::MouseRayTest(BeerEngine::GameObject *gameObject) :
Component(gameObject)
{
	
}

// ###############################################################

// OVERLOAD OPERATOR #############################################

std::ostream &				operator<<(std::ostream & o, MouseRayTest const & i)
{
	(void)i;
	return (o);
}

// ###############################################################

// PUBLIC METHOD #################################################

void MouseRayTest::start()
{
	std::cout << "MouseRayTest start" << std::endl;
	clicking = false;
}

void MouseRayTest::update()
{
	int state = glfwGetMouseButton(BeerEngine::Window::GetInstance()->getWindow(), GLFW_MOUSE_BUTTON_LEFT);
	if (state == GLFW_PRESS && !clicking)
	{
		clicking = true;
		auto ray = BeerEngine::Physics::Physics::MouseToWorldRay();
		ray.origin.y = 0.5;
		ray.direction.y = 0;
		ray.direction = glm::normalize(ray.direction);
		ray.direction *= 2;

		// BeerEngine::Physics::Physics::Raycast(ray.origin, ray.direction);
		// BeerEngine::Physics::RaycastHit hit;
		// if (BeerEngine::Physics::Physics::Raycast(ray.origin, ray.direction, hit, 1))
		// 	std::cout << "hit: " << glm::to_string(hit.transform->position) << " | " << hit.distance << std::endl;
		// BeerEngine::Physics::Physics::RaycastAll(ray.origin, ray.direction);
		// linesRenderer->addRay(ray);
	}
	else if (state == GLFW_RELEASE && clicking)
	{
		clicking = false;
	}
}

void MouseRayTest::fixedUpdate()
{
	
}

nlohmann::json	MouseRayTest::serialize()
{
	auto j = Component::serialize();
	j.merge_patch({
		{"componentClass", type},
		{"linesRenderer", SERIALIZE_BY_ID(linesRenderer)},
	});
	return j;
}

void MouseRayTest::deserialize(const nlohmann::json & j, BeerEngine::JsonLoader & loader)
{
	Component::deserialize(j, loader);
	DESERIALIZE_BY_ID(this->linesRenderer, BeerEngine::Component::RaysRenderer, "linesRenderer", loader);
}

REGISTER_COMPONENT_CPP(MouseRayTest)

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
