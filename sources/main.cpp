#include <thread>
#include "Core/BeerEngine.hpp"

#include "Game/SceneTest.hpp"

#include "Audio/AudioMaster.hpp"

static int     frameCount = 0;

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
            {
                scene->mutexLock(true);
                scene->fixedUpdate();
                scene->mutexLock(false);
            }
            fixeUpdateNumber++;
            fixedTimer -= fixedUpdateTime;
        }
        if (scene != nullptr)
        {
            scene->mutexLock(true);
            scene->update();
            scene->mutexLock(false);
        }

        if (timer >= 1.0)
        {
#ifdef BE_DEBUG
            std::cout << "FPS: " << frameCount << " - UPS: " << fixeUpdateNumber << std::endl;
#endif
            fixeUpdateNumber = 0;
            frameCount = 0;
            timer -= 1.0;
        }
    }
    std::cout << "Thread Update: Finish" << std::endl;
}

int main(void)
{
    BeerEngine::Window  *window = BeerEngine::Window::CreateWindow("Bomberman", 1280, 720);
    BeerEngine::AScene  *scene;
    BeerEngine::Graphics::Graphics::Load();
    BeerEngine::SceneManager::LoadScene<SceneTest>();
    // Thread Update
    std::thread updateLoop (updateThread, window);
    updateLoop.detach();
    // depth-testing
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    // CullFace
    glCullFace(GL_BACK);
    glEnable(GL_CULL_FACE);
    // Audio
    // AudioMaster audio;
    // FPS
    while (!glfwWindowShouldClose(window->getWindow()))
    {
        window->clear();
        scene = BeerEngine::SceneManager::GetCurrent();
        if (scene != nullptr)
        {
            scene->mutexLock(true);
            scene->renderUpdate();
            scene->render();
            scene->mutexLock(false);
        }
        window->swapBuffer();
        frameCount++;
    }
    delete BeerEngine::Camera::main;
    BeerEngine::Graphics::Graphics::UnLoad();
    delete window;
    return (0);
}
