#ifndef GAME_SCENE_RANDOM_HPP
#define GAME_SCENE_RANDOM_HPP 1

#include "Core/Core.hpp"
#include "Core/AScene.hpp"

class SceneRandom : public BeerEngine::AScene
{
public:
	void    init(void);

	template <typename T>
	BeerEngine::GameObject *addCrate(BeerEngine::Graphics::ShaderProgram *shader, glm::vec3 scale, glm::vec3 pos, BeerEngine::Component::RBType kinematic);

};

#endif
