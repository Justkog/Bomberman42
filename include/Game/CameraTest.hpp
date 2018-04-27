#ifndef GAME_CAMERA_TEST_HPP
#define GAME_CAMERA_TEST_HPP 1

#include "Core/BeerEngine.hpp"
#include "Core/AScene.hpp"

class CameraTest : public BeerEngine::GameObject
{
private:
	glm::vec3	_rotation;
public:
	CameraTest(int uniqueID, BeerEngine::AScene &scene);
	void	start(void);
	void    update(void);
};

#endif