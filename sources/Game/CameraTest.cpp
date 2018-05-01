#include "Game/CameraTest.hpp"
#include "Core/Input.hpp"
#include "Core/Time.hpp"
#include "Core/Camera.hpp"


CameraTest::CameraTest(int uniqueID, BeerEngine::AScene &scene) :
	BeerEngine::GameObject(uniqueID, scene)
{}

void	CameraTest::start(void)
{

}

void    CameraTest::update(void)
{
	// std::cout << "coucou" << std::endl;
    if (BeerEngine::Input::GetKey(BeerEngine::KeyCode::W))
	{
	    BeerEngine::Camera::main->transform.translate(BeerEngine::Camera::main->transform.forward() * BeerEngine::Time::GetDeltaTime());
	    // std::cout << "W: " << BeerEngine::Time::GetDeltaTime() << std::endl;
	}
	if (BeerEngine::Input::GetKey(BeerEngine::KeyCode::S))
	{
	    BeerEngine::Camera::main->transform.translate(BeerEngine::Camera::main->transform.forward() * -BeerEngine::Time::GetDeltaTime());
	    // std::cout << "S: " << BeerEngine::Time::GetDeltaTime() << std::endl;
	}
	if (BeerEngine::Input::GetKey(BeerEngine::KeyCode::A))
	{
	    BeerEngine::Camera::main->transform.translate(BeerEngine::Camera::main->transform.right() * BeerEngine::Time::GetDeltaTime());
	    // std::cout << "D: " << BeerEngine::Time::GetDeltaTime() << std::endl;
	}
	if (BeerEngine::Input::GetKey(BeerEngine::KeyCode::D))
	{
	    BeerEngine::Camera::main->transform.translate(BeerEngine::Camera::main->transform.right() * -BeerEngine::Time::GetDeltaTime());
	    // std::cout << "A: " << BeerEngine::Time::GetDeltaTime() << std::endl;
	}
	if (BeerEngine::Input::GetKey(BeerEngine::KeyCode::SPACE))
	{
	    BeerEngine::Camera::main->transform.translate(BeerEngine::Camera::main->transform.top() * BeerEngine::Time::GetDeltaTime());
	}
	if (BeerEngine::Input::GetKey(BeerEngine::KeyCode::LEFT_CONTROL))
	{
	    BeerEngine::Camera::main->transform.translate(BeerEngine::Camera::main->transform.top() * -BeerEngine::Time::GetDeltaTime());
	}
	if (BeerEngine::Input::GetKey(BeerEngine::KeyCode::LEFT))
	{
		_rotation[1] += -BeerEngine::Time::GetDeltaTime();
	}
	if (BeerEngine::Input::GetKey(BeerEngine::KeyCode::RIGHT))
	{
		_rotation[1] += BeerEngine::Time::GetDeltaTime();
	}
	if (BeerEngine::Input::GetKey(BeerEngine::KeyCode::UP))
	{
		_rotation[0] += BeerEngine::Time::GetDeltaTime();
	}
	if (BeerEngine::Input::GetKey(BeerEngine::KeyCode::DOWN))
	{
		_rotation[0] += -BeerEngine::Time::GetDeltaTime();
	}
	glm::quat quat = glm::angleAxis(_rotation[0], glm::vec3(1, 0, 0)) * glm::angleAxis(_rotation[1], glm::vec3(0, 1, 0));
	BeerEngine::Camera::main->transform.rotation = quat;
}
