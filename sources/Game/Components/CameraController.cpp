#include "Game/Components/CameraController.hpp"
#include "Core/Input.hpp"
#include "Core/Time.hpp"

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
			this->cam->transform.rotation = this->cam->transform.rotation * glm::angleAxis((float)M_PI, glm::vec3(0, 1, 0));
		}

		void    CameraController::fixedUpdate(void)
		{

		}

		void    CameraController::update(void)
		{
			float rotation_y = 0;
			float rotation_x = 0;
			if (BeerEngine::Input::GetKey(BeerEngine::KeyCode::W))
				cam->transform.translate(cam->transform.forward() * BeerEngine::Time::GetDeltaTime());
			if (BeerEngine::Input::GetKey(BeerEngine::KeyCode::S))
				cam->transform.translate(-cam->transform.forward() * BeerEngine::Time::GetDeltaTime());
			if (BeerEngine::Input::GetKey(BeerEngine::KeyCode::A))
				cam->transform.translate(cam->transform.left() * BeerEngine::Time::GetDeltaTime());
			if (BeerEngine::Input::GetKey(BeerEngine::KeyCode::D))
				cam->transform.translate(cam->transform.right() * BeerEngine::Time::GetDeltaTime());
			if (BeerEngine::Input::GetKey(BeerEngine::KeyCode::SPACE))
				cam->transform.translate(cam->transform.top() * BeerEngine::Time::GetDeltaTime());
			if (BeerEngine::Input::GetKey(BeerEngine::KeyCode::LEFT_CONTROL))
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