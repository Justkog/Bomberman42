#include "Game/Components/CameraController.hpp"
#include "Core/Input.hpp"
#include "Game/Input.hpp"
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
			// this->cam->transform.position = glm::vec3(0, 10, 0);
			// this->cam->transform.rotation = this->cam->transform.rotation * glm::angleAxis((float)3.14f, glm::vec3(0, 1, 0)) * glm::angleAxis((float)-1.0f, glm::vec3(1, 0, 0));
			this->_gameObject->transform.position = glm::vec3(0, 10, 0);
			this->_gameObject->transform.rotation = this->_gameObject->transform.rotation * glm::angleAxis((float)3.14f, glm::vec3(0, 1, 0)) * glm::angleAxis((float)-1.0f, glm::vec3(1, 0, 0));

			syncCam();
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
			if (BeerEngine::Input::GetKey(Game::Input::keyBindings["move up"]))
				_gameObject->transform.translate(_gameObject->transform.forward() * cam_speed * BeerEngine::Time::GetDeltaTime());
			if (BeerEngine::Input::GetKey(Game::Input::keyBindings["move down"]))
				_gameObject->transform.translate(-_gameObject->transform.forward() * cam_speed * BeerEngine::Time::GetDeltaTime());
			if (BeerEngine::Input::GetKey(Game::Input::keyBindings["move left"]))
				_gameObject->transform.translate(_gameObject->transform.left() * cam_speed * BeerEngine::Time::GetDeltaTime());
			if (BeerEngine::Input::GetKey(Game::Input::keyBindings["move right"]))
				_gameObject->transform.translate(_gameObject->transform.right() * cam_speed * BeerEngine::Time::GetDeltaTime());
			if (BeerEngine::Input::GetKey(BeerEngine::KeyCode::C))
				_gameObject->transform.translate(_gameObject->transform.top() * BeerEngine::Time::GetDeltaTime());
			if (BeerEngine::Input::GetKey(BeerEngine::KeyCode::X))
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


			// TEST :
			// std::cout << "Mouse X: " << BeerEngine::Input::GetAxis("Mouse X") << std::endl;
			syncCam();
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
