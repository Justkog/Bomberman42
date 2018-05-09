#include "Core/SceneManager.hpp"

namespace BeerEngine
{
	AScene		*SceneManager::_Current = nullptr;
	AScene		*SceneManager::_Next = nullptr;
	AScene		*SceneManager::_Old = nullptr;

	AScene		*SceneManager::GetCurrent(void)
	{
		if (_Next)
		{
			_Old = _Current;
			_Current = _Next;
			_Next = nullptr;
		}
		else if (_Old)
		{
			delete _Old;
			_Old = nullptr;
		}
		return (_Current);
	}
}