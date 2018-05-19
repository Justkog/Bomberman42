#ifndef SCENELOADER_HPP
# define SCENELOADER_HPP

/*!
 * \file SceneLoader.hpp
 * \brief Chargeur de scene sur base du nom de sa classe.
 * \author jblondea
 */

#include "Core/Core.hpp"
#include "Game/Game.hpp"

namespace Game
{
	typedef void (*LoadScene)(void); // scene load function pointer type

	class SceneLoader
	{
	public:
		static std::map<std::string, LoadScene> nameToLoad;
		static void loadByName(std::string name);

		std::string name;
		void load();

	};
}

#endif
