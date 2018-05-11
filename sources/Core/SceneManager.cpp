#include "Core/SceneManager.hpp"
#include <thread>

namespace BeerEngine
{
	AScene		*SceneManager::_Current = nullptr;
	AScene		*SceneManager::_Next = nullptr;
	bool		SceneManager::_updateThreadWaiting = false;

	AScene		*SceneManager::GetCurrent(bool isRenderThread)
	{
		if (!isRenderThread)
		{
			while (_Next)
			{
				// std::cout << "update thread waiting" << std::endl;
				_updateThreadWaiting = true;
				std::this_thread::sleep_for(std::chrono::milliseconds(1));
			}
			_updateThreadWaiting = false;
		}
		else if (_Next)
		{
			while (!_updateThreadWaiting)
			{
				// std::cout << "render thread waiting for update thread to complete and wait" << std::endl;
				std::this_thread::sleep_for(std::chrono::milliseconds(1));
			}
			delete _Current;
			_Current = _Next;
			_Current->start();
			_Next = nullptr;
		}
		return (_Current);
	}
}