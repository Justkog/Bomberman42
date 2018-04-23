#include "Core/AScene.hpp"

namespace BeerEngine
{
    int     AScene::uniqueID = 0;

    AScene::AScene(void)
    {
        
    }

    AScene::~AScene(void)
    {
        std::map<int, GameObject *>::iterator it;
        for (it = _gameObjects.begin(); it != _gameObjects.end(); ++it)
        {
            delete (it->second);
        }
        _gameObjects.clear();
    }

     void    AScene::mutexLock(bool lock)
     {
        if (lock)
            updateMutex.lock();
        else
            updateMutex.unlock();
     }

    void    AScene::start(void)
    {
        std::map<int, GameObject *>::iterator it;
        for (it = _gameObjects.begin(); it != _gameObjects.end(); ++it)
        {
            (it->second)->start();
            (it->second)->componentStart();
        }
    }

    void    AScene::fixedUpdate(void)
    {
        std::map<int, GameObject *>::iterator it;
        for (it = _gameObjects.begin(); it != _gameObjects.end(); ++it)
        {
            (it->second)->fixedUpdate();
            (it->second)->componentFixedUpdate();
        }
    }

    void    AScene::update(void)
    {
        std::map<int, GameObject *>::iterator it;
        for (it = _gameObjects.begin(); it != _gameObjects.end(); ++it)
        {
            (it->second)->update();
            (it->second)->componentUpdate();
        }
    }

    void    AScene::renderUpdate(void)
    {
        std::map<int, GameObject *>::iterator it;
        for (it = _gameObjects.begin(); it != _gameObjects.end(); ++it)
        {
            (it->second)->renderUpdate();
            (it->second)->componentRenderUpdate();
        }
    }

    void    AScene::render(void)
    {
        std::map<int, GameObject *>::iterator it;
        for (it = _gameObjects.begin(); it != _gameObjects.end(); ++it)
        {
            (it->second)->render();
            (it->second)->componentRender();
        }
    }

}