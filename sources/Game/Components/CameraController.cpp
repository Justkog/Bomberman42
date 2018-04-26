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
			_gameObject->transform.position = glm::vec3(0, -10, 0);
			_gameObject->transform.rotation = this->cam->transform.rotation * glm::angleAxis((float)M_PI, glm::vec3(0, 1, 0)) * glm::angleAxis((float)-M_PI_4, glm::vec3(1, 0, 0));
			syncCam();
		}

		void    CameraController::fixedUpdate(void)
		{

		}

		void    CameraController::update(void)
		{
			float rotation_y = 0;
			float rotation_x = 0;
			if (BeerEngine::Input::GetKey(BeerEngine::KeyCode::W))
				_gameObject->transform.translate(_gameObject->transform.forward() * BeerEngine::Time::GetDeltaTime());
			if (BeerEngine::Input::GetKey(BeerEngine::KeyCode::S))
				_gameObject->transform.translate(-_gameObject->transform.forward() * BeerEngine::Time::GetDeltaTime());
			if (BeerEngine::Input::GetKey(BeerEngine::KeyCode::A))
				_gameObject->transform.translate(_gameObject->transform.left() * BeerEngine::Time::GetDeltaTime());
			if (BeerEngine::Input::GetKey(BeerEngine::KeyCode::D))
				_gameObject->transform.translate(_gameObject->transform.right() * BeerEngine::Time::GetDeltaTime());
			if (BeerEngine::Input::GetKey(BeerEngine::KeyCode::SPACE))
				_gameObject->transform.translate(_gameObject->transform.top() * BeerEngine::Time::GetDeltaTime());
			if (BeerEngine::Input::GetKey(BeerEngine::KeyCode::LEFT_CONTROL))
				_gameObject->transform.translate(-_gameObject->transform.top() * BeerEngine::Time::GetDeltaTime());
			if (BeerEngine::Input::GetKey(BeerEngine::KeyCode::LEFT))
				rotation_y = -1 * BeerEngine::Time::GetDeltaTime();
			if (BeerEngine::Input::GetKey(BeerEngine::KeyCode::RIGHT))
				rotation_y = 1 * BeerEngine::Time::GetDeltaTime();
			if (BeerEngine::Input::GetKey(BeerEngine::KeyCode::UP))
				rotation_x = 1 * BeerEngine::Time::GetDeltaTime();
			if (BeerEngine::Input::GetKey(BeerEngine::KeyCode::DOWN))
				rotation_x = -1 * BeerEngine::Time::GetDeltaTime();

			glm::vec2 mouseDelta = BeerEngine::Input::mousePosition - this->lastMousePos;
			_gameObject->transform.rotation = _gameObject->transform.rotation * glm::angleAxis(rotation_y, glm::vec3(0, 1, 0));
			_gameObject->transform.rotation = _gameObject->transform.rotation * glm::angleAxis(rotation_x, _gameObject->transform.left());
			this->lastMousePos = BeerEngine::Input::mousePosition;

			syncCam();
		}

		// ###############################################################

		// GETTER METHOD #################################################

		// ###############################################################

		// SETTER METHOD #################################################

		// ###############################################################

		// PRIVATE METHOD ################################################

		void	CameraController::syncCam()
		{
			this->cam->transform.position = _gameObject->transform.position;
			this->cam->transform.rotation = _gameObject->transform.rotation;
		}

		// ###############################################################

		// EXCEPTION METHOD ##############################################

		// ###############################################################

		// EXTERNAL ######################################################

		// ###############################################################
	}
}