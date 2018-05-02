#include "Game/Components/MouseRayTest.hpp"
#include "Core/Input.hpp"
#include "Core/Window.hpp"
#include "Core/Camera.hpp"
#include "Core/Graphics/MeshBuilder.hpp"
#include "Core/Graphics/Graphics.hpp"
#include "Core/Graphics/Mesh.hpp"
#include "Core/Component/MeshRenderer.hpp"
#include "Core/IO/FileUtils.hpp"
#include "Core/Graphics/AMaterial.hpp"

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
	old_size = 0;

	// Shader
	BeerEngine::Graphics::ShaderProgram *shader = new BeerEngine::Graphics::ShaderProgram(2);
	shader->load(0, GL_VERTEX_SHADER,
		BeerEngine::IO::FileUtils::LoadFile("shaders/line_v.glsl").c_str()
	);
	shader->load(1, GL_FRAGMENT_SHADER,
		BeerEngine::IO::FileUtils::LoadFile("shaders/line_f.glsl").c_str()
	);
	shader->compile();
	BeerEngine::Graphics::AMaterial *material = new BeerEngine::Graphics::AMaterial(shader);
	material->setColor(glm::vec4(0.5f, 1.0f, 1.0f, 1.0f));
	linesRenderer->setMaterial(material);

	linesRenderer->renderMode = GL_LINES;
}

void MouseRayTest::RebuildMesh()
{
	BeerEngine::Graphics::MeshBuilder builder;
	for (int i = 0; i < rays.size(); i++)
	{
		auto rayEndPos = rays[i].origin + rays[i].direction;
		builder
		.addVertice(rays[i].origin)
		.addVertice(rayEndPos)
		;
	}

	auto lines = builder.build();
	linesRenderer->setMesh(lines);
}

void MouseRayTest::update()
{
	int state = glfwGetMouseButton(BeerEngine::Window::GetInstance()->getWindow(), GLFW_MOUSE_BUTTON_LEFT);
	if (state == GLFW_PRESS && !clicking)
	{
		clicking = true;
		auto ray = MouseToWorldRay();
		ray.direction *= 10;
		rays.push_back(ray);
		// for (int i = 0; i < rays.size(); i++)
		// {
		// 	std::cout << "cam is at : " << glm::to_string(BeerEngine::Camera::main->transform.position) << std::endl;
		// 	std::cout << "ray pos : " << glm::to_string(rays[i].origin) << " / ray dir : " << glm::to_string(rays[i].direction) << std::endl;
		// }
	}
	else if (state == GLFW_RELEASE && clicking)
	{
		clicking = false;
	}
}

void MouseRayTest::fixedUpdate()
{
	
}

void MouseRayTest::renderUpdate(void)
{
	if (old_size != rays.size())
	{
		RebuildMesh();
		old_size = rays.size();
	}
}

void MouseRayTest::render(void)
{

}

// ###############################################################

// GETTER METHOD #################################################

// ###############################################################

// SETTER METHOD #################################################

// ###############################################################

// PRIVATE METHOD ################################################

Game::Component::Ray MouseRayTest::ScreenToWorldRay(glm::vec2 screenPosition) {
	float pointX = screenPosition.x / (WINDOW_WIDTH  * 0.5f) - 1.0f;
    float pointY = screenPosition.y / (WINDOW_HEIGHT * 0.5f) - 1.0f;
	glm::mat4 proj = BeerEngine::Window::GetInstance()->getProjection3D();
	auto cam = BeerEngine::Camera::main;
    glm::mat4 view = glm::lookAt(glm::vec3(0.0f), cam->transform.forward(), cam->transform.top());

    glm::mat4 invVP = glm::inverse(proj * view);
    glm::vec4 screenPos = glm::vec4(pointX, -pointY, 1.0f, 1.0f);
    glm::vec4 worldPos = invVP * screenPos;

    glm::vec3 dir = glm::normalize(glm::vec3(worldPos));
	Ray ray;
	ray.origin = BeerEngine::Camera::main->transform.position;
	ray.direction = dir;

    return ray;
}

Game::Component::Ray MouseRayTest::MouseToWorldRay() {
    return ScreenToWorldRay(BeerEngine::Input::mousePosition);
}

// ###############################################################

// EXCEPTION METHOD ##############################################

// ###############################################################

// EXTERNAL ######################################################

// ###############################################################
	}
}
