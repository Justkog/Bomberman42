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
	};
}

#endif
