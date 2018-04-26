#ifndef GAME_SCENE_TEST_HPP
#define GAME_SCENE_TEST_HPP 1

#include "Core/BeerEngine.hpp"

class SceneTest : public BeerEngine::AScene
{
public:
	void    init(void);

	template <typename T>
	void addCrate(BeerEngine::Graphics::ShaderProgram *shader, glm::vec3 scale, glm::vec3 pos, bool kinematic)
	{
		BeerEngine::Component::MeshRenderer *meshRenderer;
		auto mapBlocGO = instantiate<BeerEngine::GameObject>();
		mapBlocGO->name = "map block";
		meshRenderer = mapBlocGO->AddComponent<BeerEngine::Component::MeshRenderer>();
		meshRenderer->setMesh(BeerEngine::Graphics::Graphics::cube);
		auto *mapBlocTex = BeerEngine::Graphics::Texture::LoadPNG("textures/crate1_diffuse.png");
		auto *mapBlocMat = new BeerEngine::Graphics::AMaterial(shader);
		mapBlocMat->setAlbedo(mapBlocTex);
		meshRenderer->setMaterial(mapBlocMat);
		mapBlocGO->transform.position = pos;
		mapBlocGO->transform.scale = scale;
		auto blockColl = mapBlocGO->AddComponent<T>();
		blockColl->_kinematic = kinematic;
	}
	
};

#endif