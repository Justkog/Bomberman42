#ifndef BE_CORE_SCENEMANAGER_HPP
#define BE_CORE_SCENEMANAGER_HPP 1

#include "Core.hpp"
#include "AScene.hpp"

namespace BeerEngine
{
    class SceneManager
    {
    private:
        static AScene      *_Current;
        static AScene      *_Next;
		static bool			_updateThreadWaiting;

    public:
        static AScene       *GetCurrent(bool isRenderThread);
        template<typename T, typename std::enable_if<std::is_base_of<AScene, T>::value>::type* = nullptr>
        static void         LoadScene(void)
        {
			auto nextScene = new T();
            nextScene->init();
			_Next = nextScene;
        }
    };
}

#endif