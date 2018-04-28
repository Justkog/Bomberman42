#ifndef GAME_CAMERA_TEST_HPP
#define GAME_CAMERA_TEST_HPP 1

#include "Core/Core.hpp"
#include "Core/GameObject.hpp"

class CameraTest : public BeerEngine::GameObject
{
private:
	glm::vec3	_rotation;
public:
	CameraTest(int uniqueID);
	void	start(void);
	void    update(void);
};

#endif