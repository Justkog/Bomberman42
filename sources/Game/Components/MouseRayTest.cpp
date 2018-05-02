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
		ray.direction *= 10;
		linesRenderer->addRay(ray);
	}
	else if (state == GLFW_RELEASE && clicking)
	{
		clicking = false;
	}
}

void MouseRayTest::fixedUpdate()
{
	
}

// ###############################################################

// GETTER METHOD #################################################

// ###############################################################

// SETTER METHOD #################################################

// ###############################################################

// PRIVATE METHOD ################################################

// BeerEngine::Component::Ray MouseRayTest::ScreenToWorldRay(glm::vec2 screenPosition) {
// 	float pointX = screenPosition.x / (WINDOW_WIDTH  * 0.5f) - 1.0f;
//     float pointY = screenPosition.y / (WINDOW_HEIGHT * 0.5f) - 1.0f;
// 	glm::mat4 proj = BeerEngine::Window::GetInstance()->getProjection3D();
// 	auto cam = BeerEngine::Camera::main;
//     glm::mat4 view = glm::lookAt(glm::vec3(0.0f), cam->transform.forward(), cam->transform.top());

//     glm::mat4 invVP = glm::inverse(proj * view);
//     glm::vec4 screenPos = glm::vec4(pointX, -pointY, 1.0f, 1.0f);
//     glm::vec4 worldPos = invVP * screenPos;

//     glm::vec3 dir = glm::normalize(glm::vec3(worldPos));
// 	BeerEngine::Component::Ray ray;
// 	ray.origin = BeerEngine::Camera::main->transform.position;
// 	ray.direction = dir;

//     return ray;
// }

// BeerEngine::Component::Ray MouseRayTest::MouseToWorldRay() {
//     return ScreenToWorldRay(BeerEngine::Input::mousePosition);
// }

// ###############################################################

// EXCEPTION METHOD ##############################################

// ###############################################################

// EXTERNAL ######################################################

// ###############################################################
	}
}
