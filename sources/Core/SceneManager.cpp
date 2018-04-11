#include "Core/SceneManager.hpp"

namespace BeerEngine
{
	AScene		*SceneManager::_Current = nullptr;

	AScene		*SceneManager::GetCurrent(void)
	{
		return (_Current);
	}
}