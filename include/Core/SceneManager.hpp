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
        static AScene      *_Old;

    public:
        static AScene       *GetCurrent(void);
        template<typename T, typename std::enable_if<std::is_base_of<AScene, T>::value>::type* = nullptr>
        static void         LoadScene(void)
        {
            // if (_Current != nullptr)
            //     delete _Current;
            // _Current = new T();
            // _Current->init();
            // _Current->debugTest();
			auto nextScene = new T();
            nextScene->init();
			_Next = nextScene;
            // _Next->debugTest();
        }
    };
}

#endif