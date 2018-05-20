#include "Game/Components/CameraController.hpp"
#include "Core/Input.hpp"
#include "Game/Input.hpp"
#include "Core/Time.hpp"
#include "Core/Camera.hpp"
#include "Game/Components/Map.hpp"
#include "Game/Components/Player.hpp"
#include "Game/Components/Character.hpp"

namespace Game
{
	namespace Component
	{
		// STATIC ########################################################

		// ###############################################################

		// CANONICAL #####################################################

		CameraController::CameraController ( void )
		{
			return ;
		}

		CameraController::CameraController ( CameraController const & src )
		{
			*this = src;
			return ;
		}

		CameraController &				CameraController::operator=( CameraController const & rhs )
		{
			(void) rhs;
			if (this != &rhs)
			{}
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
			Player		*player = Player::instance;
			startAnimation = false;
			timeAnimation = 0.0f;
			if (player)
			{
				this->_gameObject->transform.position = player->_gameObject->transform.position + glm::vec3(0, 1.0f, 0.0f);
			}
			this->_gameObject->transform.rotation = glm::angleAxis((float)3.14f, glm::vec3(0, 1, 0)) * glm::angleAxis((float)-1.57f, glm::vec3(1, 0, 0));
			tpsCamera = false;
			syncCam();
		}

		void			CameraController::animationStart()
		{
			Player		*player = Player::instance;
			startAnimation = true;
			timeAnimation = 0.0f;
			if (player)
			{
				this->_gameObject->transform.position = player->_gameObject->transform.position + glm::vec3(0, 1.0f, 0.0f);
				this->_gameObject->transform.rotation = glm::angleAxis((float)3.14f, glm::vec3(0, 1, 0)) * glm::angleAxis((float)-1.57f, glm::vec3(1, 0, 0));
			}
		}

		void    CameraController::fixedUpdate(void)
		{
			if (startAnimation)
				return;
			if (BeerEngine::Input::GetKeyDown(Game::Input::keyBindings["change view"]))
				tpsCamera = !tpsCamera;
			if (tpsCamera)
			{
				Player		*player = Player::instance;
				if (player)
				{
					this->_gameObject->transform.position = player->_gameObject->transform.position + glm::vec3(0, 10, -1.5f);
					this->_gameObject->transform.rotation = glm::angleAxis((float)3.14f, glm::vec3(0, 1, 0)) * glm::angleAxis((float)-1.3f, glm::vec3(1, 0, 0));
				}
			}
			else
			{
				Map	*map = Map::instance;
				if (map)
				{
					float y = map->_sizeX;
					if (y < 10)
						y = 10;
					this->_gameObject->transform.position = glm::vec3(0, y, map->_sizeY / 3.0f);
					this->_gameObject->transform.rotation = glm::angleAxis((float)3.14f, glm::vec3(0, 1, 0)) * glm::angleAxis((float)-1.3f, glm::vec3(1, 0, 0));
					// std::cout << map->_sizeX << ", " << map->_sizeY << std::endl;
					//_sizeX
					//_sizeY
				}
			}
		}

		void    CameraController::update(void)
		{
			if (startAnimation)
			{
				if (timeAnimation >= 5.0f)
					startAnimation = false;

				float t = timeAnimation / 5.0f;
				Map		*map = Map::instance;
				Player	*player = Player::instance;
				if (map && player)
				{
					t = glm::sin(t * glm::radians(90.0f));
					float y = map->_sizeX;
					if (y < 10)
						y = 10;
					this->_gameObject->transform.position = glm::mix(player->_gameObject->transform.position + glm::vec3(0, 1.0f, 0.0f), glm::vec3(0, y, map->_sizeY / 3.0f), t);
					this->_gameObject->transform.rotation = glm::mix(
						glm::angleAxis((float)3.14f, glm::vec3(0, 1, 0)) * glm::angleAxis((float)-1.57f, glm::vec3(1, 0, 0)),
						glm::angleAxis((float)3.14f, glm::vec3(0, 1, 0)) * glm::angleAxis((float)-1.3f, glm::vec3(1, 0, 0)),
						t
					);
				}
				timeAnimation += BeerEngine::Time::GetDeltaTime();
				if (timeAnimation > 5.0f)
					timeAnimation = 5.0f;
			}
			// float rotation_y = 0;
			// float rotation_x = 0;
			// float cam_speed = 1;
			// if (BeerEngine::Input::GetKey(BeerEngine::KeyCode::LEFT_SHIFT))
			// 	cam_speed = 10;
			// if (BeerEngine::Input::GetKey(BeerEngine::KeyCode::W))
			// 	_gameObject->transform.translate(_gameObject->transform.forward() * cam_speed * BeerEngine::Time::GetDeltaTime());
			// if (BeerEngine::Input::GetKey(BeerEngine::KeyCode::S))
			// 	_gameObject->transform.translate(-_gameObject->transform.forward() * cam_speed * BeerEngine::Time::GetDeltaTime());
			// if (BeerEngine::Input::GetKey(BeerEngine::KeyCode::A))
			// 	_gameObject->transform.translate(_gameObject->transform.left() * cam_speed * BeerEngine::Time::GetDeltaTime());
			// if (BeerEngine::Input::GetKey(BeerEngine::KeyCode::D))
			// 	_gameObject->transform.translate(_gameObject->transform.right() * cam_speed * BeerEngine::Time::GetDeltaTime());
			// if (BeerEngine::Input::GetKey(BeerEngine::KeyCode::C))
			// 	_gameObject->transform.translate(_gameObject->transform.top() * BeerEngine::Time::GetDeltaTime());
			// if (BeerEngine::Input::GetKey(BeerEngine::KeyCode::X))
			// 	_gameObject->transform.translate(-_gameObject->transform.top() * BeerEngine::Time::GetDeltaTime());

			// if (BeerEngine::Input::GetKey(BeerEngine::KeyCode::W))
			// 	cam->transform.translate(cam->transform.forward() * cam_speed * BeerEngine::Time::GetDeltaTime());
			// if (BeerEngine::Input::GetKey(BeerEngine::KeyCode::S))
			// 	cam->transform.translate(-cam->transform.forward() * cam_speed * BeerEngine::Time::GetDeltaTime());
			// if (BeerEngine::Input::GetKey(BeerEngine::KeyCode::A))
			// 	cam->transform.translate(cam->transform.left() * cam_speed * BeerEngine::Time::GetDeltaTime());
			// if (BeerEngine::Input::GetKey(BeerEngine::KeyCode::D))
			// 	cam->transform.translate(cam->transform.right() * cam_speed * BeerEngine::Time::GetDeltaTime());
			
			// if (BeerEngine::Input::GetKey(BeerEngine::KeyCode::LEFT))
			// 	rotation_y = -1 * BeerEngine::Time::GetDeltaTime();
			// if (BeerEngine::Input::GetKey(BeerEngine::KeyCode::RIGHT))
			// 	rotation_y = 1 * BeerEngine::Time::GetDeltaTime();
			// if (BeerEngine::Input::GetKey(BeerEngine::KeyCode::UP))
			// 	rotation_x = 1 * BeerEngine::Time::GetDeltaTime();
			// if (BeerEngine::Input::GetKey(BeerEngine::KeyCode::DOWN))
			// 	rotation_x = -1 * BeerEngine::Time::GetDeltaTime();

			// glm::vec2 mouseDelta = BeerEngine::Input::mousePosition - this->lastMousePos;
			// cam->transform.rotation = cam->transform.rotation * glm::angleAxis(rotation_y, glm::vec3(0, 1, 0));
			// cam->transform.rotation = cam->transform.rotation * glm::angleAxis(rotation_x, cam->transform.left());
			// _gameObject->transform.rotation = _gameObject->transform.rotation * glm::angleAxis(rotation_y, glm::vec3(0, 1, 0));
			// _gameObject->transform.rotation = _gameObject->transform.rotation * glm::angleAxis(rotation_x, _gameObject->transform.left());
			// this->lastMousePos = BeerEngine::Input::mousePosition;


			// TEST :
			// std::cout << "Mouse X: " << BeerEngine::Input::GetAxis("Mouse X") << std::endl;
			syncCam();
		}

		nlohmann::json	CameraController::serialize()
		{
			auto j = Component::serialize();
			j.merge_patch({
				{"componentClass", type},
			});
			return j;
		}

		void CameraController::deserialize(const nlohmann::json & j, BeerEngine::JsonLoader & loader)
		{
			Component::deserialize(j, loader);
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
