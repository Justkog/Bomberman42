#include "Game/CameraTest.hpp"

CameraTest::CameraTest(int uniqueID) :
	BeerEngine::GameObject(uniqueID)
{}

void	CameraTest::start(void)
{

}

void    CameraTest::update(void)
{
	// // std::cout << "coucou" << std::endl;
    if (BeerEngine::Input::GetKey(BeerEngine::KeyCode::W))
	{
	    BeerEngine::Camera::main->transform.translate(BeerEngine::Camera::main->transform.forward() * BeerEngine::Time::GetDeltaTime());
	}
	if (BeerEngine::Input::GetKey(BeerEngine::KeyCode::S))
	{
	    BeerEngine::Camera::main->transform.translate(BeerEngine::Camera::main->transform.forward() * -BeerEngine::Time::GetDeltaTime());
	}
	if (BeerEngine::Input::GetKey(BeerEngine::KeyCode::A))
	{
	    BeerEngine::Camera::main->transform.translate(BeerEngine::Camera::main->transform.straf() * -BeerEngine::Time::GetDeltaTime());
	}
	if (BeerEngine::Input::GetKey(BeerEngine::KeyCode::D))
	{
	    BeerEngine::Camera::main->transform.translate(BeerEngine::Camera::main->transform.straf() * BeerEngine::Time::GetDeltaTime());
	}
	if (BeerEngine::Input::GetKey(BeerEngine::KeyCode::SPACE))
	{
	    BeerEngine::Camera::main->transform.translate(BeerEngine::Maths::Vector3f(0, 1, 0) * BeerEngine::Time::GetDeltaTime());
	}
	if (BeerEngine::Input::GetKey(BeerEngine::KeyCode::LEFT_CONTROL))
	{
	    BeerEngine::Camera::main->transform.translate(BeerEngine::Maths::Vector3f(0, -1, 0) * BeerEngine::Time::GetDeltaTime());
	}
	if (BeerEngine::Input::GetKey(BeerEngine::KeyCode::LEFT))
	{
		BeerEngine::Camera::main->transform.rotation[1] += -BeerEngine::Time::GetDeltaTime();
	}
	if (BeerEngine::Input::GetKey(BeerEngine::KeyCode::RIGHT))
	{
		BeerEngine::Camera::main->transform.rotation[1] += BeerEngine::Time::GetDeltaTime();
	}
	if (BeerEngine::Input::GetKey(BeerEngine::KeyCode::UP))
	{
		BeerEngine::Camera::main->transform.rotation[0] += BeerEngine::Time::GetDeltaTime();
	}
	if (BeerEngine::Input::GetKey(BeerEngine::KeyCode::DOWN))
	{
		BeerEngine::Camera::main->transform.rotation[0] += -BeerEngine::Time::GetDeltaTime();
	}
	// glm::quat quat = glm::angleAxis(_rotation[0], glm::vec3(1, 0, 0)) * glm::angleAxis(_rotation[1], glm::vec3(0, 1, 0));
	// BeerEngine::Camera::main->transform.rotation = quat;
}
