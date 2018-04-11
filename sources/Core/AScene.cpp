#include "Core/AScene.hpp"

namespace BeerEngine
{
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
    }

    void    AScene::fixedUpdate(void)
    {

    }

    void    AScene::update(void)
    {

    }

    void    AScene::renderUpdate(void)
    {

    }

    void    AScene::render(void)
    {

    }

}