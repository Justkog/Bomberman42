#include <thread>
#include "Core/Window.hpp"
#include "Core/Time.hpp"
#include "Core/AScene.hpp"
#include "Core/SceneManager.hpp"

void updateThread(BeerEngine::Window *window)
{
    static const double fixedUpdateTime = 1.0 / 60.0;
    double  fixedTimer = 0.0;
    double  timer = 0.0;
    int     fixeUpdateNumber = 0;
    BeerEngine::AScene  *scene;
    std::cout << "Thread Update: Started" << std::endl;
    while (!glfwWindowShouldClose(window->getWindow()))
    {
        scene = BeerEngine::SceneManager::GetCurrent();
        BeerEngine::Time::Update();
        fixedTimer += BeerEngine::Time::GetDeltaTime();
        timer += BeerEngine::Time::GetDeltaTime();
        while (fixedTimer >= fixedUpdateTime)
        {
            if (scene != nullptr)
                scene->fixedUpdate();
            fixeUpdateNumber++;
            fixedTimer -= fixedUpdateTime;
        }
        if (scene != nullptr)
            scene->update();
        if (timer >= 1.0)
        {
            #ifdef BE_DEBUG
            std::cout << "Fixed Update Number: " << fixeUpdateNumber << std::endl;
            #endif
            fixeUpdateNumber = 0;
            timer -= 1.0;
        }
    }
    std::cout << "Thread Update: Finish" << std::endl;
}

int main(void)
{
    BeerEngine::Window *window = BeerEngine::Window::CreateWindow("Bomberman", 1280, 720);
    BeerEngine::AScene  *scene;

    std::thread updateLoop (updateThread, window);
    updateLoop.detach();
    while (!glfwWindowShouldClose(window->getWindow()))
    {
        window->clear();
        scene = BeerEngine::SceneManager::GetCurrent();
        if (scene != nullptr)
        {
            scene->renderUpdate();
            scene->render();
        }
        window->swapBuffer();
    }
    delete window;
    return (0);
}