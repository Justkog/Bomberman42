#include <thread>
#include <chrono>
#include "Core/BeerEngine.hpp"

#include "Game/SceneTest.hpp"
#include "Game/Assets.hpp"

static int     frameCount = 0;



void updateThread(BeerEngine::Window *window)
{
    static const double fixedUpdateTime = 1.0 / 60.0;
    static const double sleepTime = fixedUpdateTime / 2.0;
    double  fixedTimer = 0.0;
    double  timer = 0.0;
    int     fixeUpdateNumber = 0;
    BeerEngine::AScene  *scene;
    std::cout << "Thread Update: Started" << std::endl;
    while (!window->isClose())
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
                scene->physicUpdate();
                scene->mutexLock(false);
            }
            fixeUpdateNumber++;
            fixedTimer -= fixedUpdateTime;
        }
        if (BeerEngine::Input::GetKeyDown(BeerEngine::KeyCode::ESCAPE))
            window->closeRequest();
        if (scene != nullptr)
        {
            scene->mutexLock(true);
            scene->update();
            scene->destroyGameObjects();
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
        //  std::this_thread::sleep_for(sleepTime);

         std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
    std::cout << "Thread Update: Finish" << std::endl;
}

int main(void)
{
    std::srand(std::time(nullptr));
    BeerEngine::Window  *window = BeerEngine::Window::CreateWindow("Bomberman", 1280, 720);
    BeerEngine::AScene  *scene;
    // Audio
    BeerEngine::Audio::AudioListener::init();
    // Graphics
    BeerEngine::Graphics::Graphics::Load();
    // Game Assets
    Assets::GetInstance()->load();
    // First Scene
    BeerEngine::SceneManager::LoadScene<SceneTest>();
    // Thread Update
    std::thread updateLoop (updateThread, window);
    updateLoop.detach();
    // depth-testing
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    // Blend Alpha
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    // CullFace
    glCullFace(GL_FRONT);
    glEnable(GL_CULL_FACE);
    // FPS
    while (!window->isClose())
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
    BeerEngine::Audio::AudioListener::DestroyOpenAL();
    delete BeerEngine::Camera::main;
    Assets::GetInstance()->unload();
    delete Assets::GetInstance();
    BeerEngine::Graphics::Graphics::UnLoad();
    delete window;
    return (0);
}
