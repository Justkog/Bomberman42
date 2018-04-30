#ifndef GAME_SCENE_TEST_HPP
#define GAME_SCENE_TEST_HPP 1

#include "Core/Component/RigidBody2D.hpp"
#include "Core/BeerEngine.hpp"
#include "Assets.hpp"

class SceneTest : public BeerEngine::AScene
{
public:
	void    init(void);

	template <typename T>
	BeerEngine::GameObject *addCrate(BeerEngine::Graphics::ShaderProgram *shader, glm::vec3 scale, glm::vec3 pos, bool kinematic)
	{
		BeerEngine::Component::MeshRenderer *meshRenderer;
		auto mapBlocGO = instantiate<BeerEngine::GameObject>();
		mapBlocGO->name = "map block";
		meshRenderer = mapBlocGO->AddComponent<BeerEngine::Component::MeshRenderer>();
		meshRenderer->setMesh(BeerEngine::Graphics::Graphics::cube);
		auto *mapBlocTex = Assets::GetTexture("textures/crate1_diffuse.png"); //BeerEngine::Graphics::Texture::LoadPNG("assets/textures/crate1_diffuse.png");
		auto *mapBlocMat = new BeerEngine::Graphics::AMaterial(shader);
		mapBlocMat->setAlbedo(mapBlocTex);
		meshRenderer->setMaterial(mapBlocMat);
		mapBlocGO->transform.position = pos;
		mapBlocGO->transform.scale = scale;
		auto blockColl = mapBlocGO->AddComponent<T>();
		if (!kinematic)
		{
			auto rb2d = mapBlocGO->AddComponent<BeerEngine::Component::RigidBody2D>();
			rb2d->kinematic = kinematic;
			rb2d->mass = 100.0f;
		}

		return (mapBlocGO);
	}

};

#endif
