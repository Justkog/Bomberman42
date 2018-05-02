#include "Game/Components/CameraController.hpp"
#include "Core/Input.hpp"
#include "Core/Time.hpp"
#include "Core/Camera.hpp"

namespace Game
{
	namespace Component
	{
		// STATIC ########################################################

		// ###############################################################

		// CANONICAL #####################################################

		// CameraController::CameraController ( void )
		// {
		// 	return ;
		// }

		// CameraController::CameraController ( CameraController const & src )
		// {
		// 	*this = src;
		// 	return ;
		// }

		CameraController &				CameraController::operator=( CameraController const & rhs )
		{
			if (this != &rhs)
			{
				// make stuff
			}
			return (*this);
		}

		CameraController::~CameraController ( void )
		{
			return ;
		}

		// ###############################################################

		// CONSTRUCTOR POLYMORPHISM ######################################

		CameraController::CameraController(BeerEngine::GameObject *gameObject) :
					Component(gameObject)
		{

		}

		// ###############################################################

		// OVERLOAD OPERATOR #############################################

		std::ostream &				operator<<(std::ostream & o, CameraController const & i)
		{
			(void)i;
			return (o);
		}

		// ###############################################################

		// PUBLIC METHOD #################################################

		void    CameraController::start(void)
		{
			std::cout << "cam start" << "\n";
			this->cam = BeerEngine::Camera::main;
			this->lastMousePos = BeerEngine::Input::mousePosition;
			this->cam->transform.position = glm::vec3(0, 10, 0);
			this->cam->transform.rotation = this->cam->transform.rotation * glm::angleAxis((float)3.14f, glm::vec3(0, 1, 0)) * glm::angleAxis((float)0.0f, glm::vec3(1, 0, 0));
		}

		void    CameraController::fixedUpdate(void)
		{

		}

		void    CameraController::update(void)
		{
			float rotation_y = 0;
			float rotation_x = 0;
			float cam_speed = 1;
			if (BeerEngine::Input::GetKey(BeerEngine::KeyCode::LEFT_SHIFT))
				cam_speed = 10;
			if (BeerEngine::Input::GetKey(BeerEngine::KeyCode::W))
				cam->transform.translate(cam->transform.forward() * cam_speed * BeerEngine::Time::GetDeltaTime());
			if (BeerEngine::Input::GetKey(BeerEngine::KeyCode::S))
				cam->transform.translate(-cam->transform.forward() * cam_speed * BeerEngine::Time::GetDeltaTime());
			if (BeerEngine::Input::GetKey(BeerEngine::KeyCode::A))
				cam->transform.translate(cam->transform.left() * cam_speed * BeerEngine::Time::GetDeltaTime());
			if (BeerEngine::Input::GetKey(BeerEngine::KeyCode::D))
				cam->transform.translate(cam->transform.right() * cam_speed * BeerEngine::Time::GetDeltaTime());
			if (BeerEngine::Input::GetKey(BeerEngine::KeyCode::SPACE))
				cam->transform.translate(cam->transform.top() * BeerEngine::Time::GetDeltaTime());
			if (BeerEngine::Input::GetKey(BeerEngine::KeyCode::X))
				cam->transform.translate(-cam->transform.top() * BeerEngine::Time::GetDeltaTime());
			if (BeerEngine::Input::GetKey(BeerEngine::KeyCode::LEFT))
				rotation_y = -1 * BeerEngine::Time::GetDeltaTime();
			if (BeerEngine::Input::GetKey(BeerEngine::KeyCode::RIGHT))
				rotation_y = 1 * BeerEngine::Time::GetDeltaTime();
			if (BeerEngine::Input::GetKey(BeerEngine::KeyCode::UP))
				rotation_x = 1 * BeerEngine::Time::GetDeltaTime();
			if (BeerEngine::Input::GetKey(BeerEngine::KeyCode::DOWN))
				rotation_x = -1 * BeerEngine::Time::GetDeltaTime();

			glm::vec2 mouseDelta = BeerEngine::Input::mousePosition - this->lastMousePos;
			cam->transform.rotation = cam->transform.rotation * glm::angleAxis(rotation_y, glm::vec3(0, 1, 0));
			cam->transform.rotation = cam->transform.rotation * glm::angleAxis(rotation_x, cam->transform.left());
			this->lastMousePos = BeerEngine::Input::mousePosition;


			// TEST :
			// std::cout << "Mouse X: " << BeerEngine::Input::GetAxis("Mouse X") << std::endl;
		}

		nlohmann::json	CameraController::serialize()
		{
			return nlohmann::json {
				{"componentClass", typeid(CameraController).name()},
			};
		}

		void CameraController::deserialize(const nlohmann::json & j)
		{
			// this->_size = j.at("size");
		}

		REGISTER_COMPONENT_CPP(CameraController)

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
