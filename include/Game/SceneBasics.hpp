#ifndef SCENEBASICS_HPP
# define SCENEBASICS_HPP

/*!
 * \file SceneLoader.hpp
 * \brief Chargeur de scene sur base du nom de sa classe.
 * \author jblondea
 */

#include "Core/Core.hpp"
#include "Game/Game.hpp"

namespace Game
{
	class SceneBasics
	{
	public:
		static void	CreateCameraBasics(BeerEngine::GameObject *cameraGO);
		static void	CreatePlayerBasics(BeerEngine::GameObject *playerGO, Component::GameManager *gameManager, int bombNumber);
		static void	CreateModelBasics(BeerEngine::GameObject *playerGO, const std::string &model, const std::string &texture, const BeerEngine::Transform &transform);
		static void GenerateDecorations(BeerEngine::AScene *scene, glm::vec2 max, glm::vec2 min, glm::vec2 mapA, glm::vec2 mapB);
		static void GeneratePlane(BeerEngine::AScene *scene, 
		std::string texturePath, 
		glm::vec2 tiling, glm::vec2 offset, 
		glm::vec3 position, glm::vec3 scale);

	};
}

#endif
