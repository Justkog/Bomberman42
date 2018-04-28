#ifndef GAME_SCENE_TEST_HPP
#define GAME_SCENE_TEST_HPP 1

namespace BeerEngine
{
	namespace Component
	{
		class Component;
		class MeshRenderer;
	}
}

#include "Core/AScene.hpp"

class SceneTest : public BeerEngine::AScene
{
public:
	void    init(void);

	template <typename T>
	BeerEngine::GameObject *addCrate(BeerEngine::Graphics::ShaderProgram *shader, glm::vec3 scale, glm::vec3 pos, bool kinematic);
	
};

#endif