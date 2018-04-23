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
			std::cout << "start" << "\n";
			this->cam = BeerEngine::Camera::main;
			this->lastMousePos = BeerEngine::Input::mousePosition;
		}

		void    CameraController::fixedUpdate(void)
		{

		}

		void    CameraController::update(void)
		{
			// if (BeerEngine::Input::GetKey(BeerEngine::KeyCode::W))
			// 	cam->transform.translate(cam->transform.forward() * BeerEngine::Time::GetDeltaTime());
			// if (BeerEngine::Input::GetKey(BeerEngine::KeyCode::S))
			// 	cam->transform.translate(-cam->transform.forward() * BeerEngine::Time::GetDeltaTime());
			// if (BeerEngine::Input::GetKey(BeerEngine::KeyCode::A))
			// 	cam->transform.translate(-cam->transform.right() * BeerEngine::Time::GetDeltaTime());
			// if (BeerEngine::Input::GetKey(BeerEngine::KeyCode::D))
			// 	cam->transform.translate(cam->transform.right() * BeerEngine::Time::GetDeltaTime());

			glm::vec2 mouseDelta = BeerEngine::Input::mousePosition - this->lastMousePos;
			glm::vec3 EulerAngles(BeerEngine::Time::GetDeltaTime() * mouseDelta.y, BeerEngine::Time::GetDeltaTime() * mouseDelta.x, 0);
			auto MyQuaternion = glm::quat(EulerAngles);
			cam->transform.rotation = MyQuaternion * cam->transform.rotation;
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