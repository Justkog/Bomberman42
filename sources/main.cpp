#include <thread>
#include <chrono>
#include "Core/BeerEngine.hpp"

#include "Game/SceneTest.hpp"

#include "Audio/AudioListener.hpp"
#include "Audio/AudioSource.hpp"
#include "Audio/AudioClip.hpp"

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
                scene->mutexLock(false);
            }
            fixeUpdateNumber++;
            fixedTimer -= fixedUpdateTime;
        }
        if (BeerEngine::Input::GetKeyDown(BeerEngine::KeyCode::ESCAPE))
            window->closeRequest();
        // if (BeerEngine::Input::GetKey(BeerEngine::KeyCode::W))
        // {
        //     BeerEngine::Camera::main->transform.translate(BeerEngine::Camera::main->transform.forward() * BeerEngine::Time::GetDeltaTime());
        //     // std::cout << "W: " << BeerEngine::Time::GetDeltaTime() << std::endl;
        // }
        // if (BeerEngine::Input::GetKey(BeerEngine::KeyCode::S))
        // {
        //     BeerEngine::Camera::main->transform.translate(BeerEngine::Camera::main->transform.forward() * -BeerEngine::Time::GetDeltaTime());
        //     // std::cout << "S: " << BeerEngine::Time::GetDeltaTime() << std::endl;
        // }
        // if (BeerEngine::Input::GetKey(BeerEngine::KeyCode::D))
        // {
        //     BeerEngine::Camera::main->transform.translate(BeerEngine::Camera::main->transform.right() * BeerEngine::Time::GetDeltaTime());
        //     // std::cout << "D: " << BeerEngine::Time::GetDeltaTime() << std::endl;
        // }
        // if (BeerEngine::Input::GetKey(BeerEngine::KeyCode::A))
        // {
        //     BeerEngine::Camera::main->transform.translate(BeerEngine::Camera::main->transform.right() * -BeerEngine::Time::GetDeltaTime());
        //     // std::cout << "A: " << BeerEngine::Time::GetDeltaTime() << std::endl;
        // }
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
        //  std::this_thread::sleep_for(sleepTime);
        
         std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
    std::cout << "Thread Update: Finish" << std::endl;
}

int main(void)
{
    // Audio
    // AudioListener::init();
    // AudioListener audio;
    //
    // audio.setListenerData(0, 0, 0);
    //
    // AudioClip   clip("assets/sounds/samplemono.wav");
    // AudioClip   clip2("assets/sounds/ds_brush_snaremono.wav");
    //
    // AudioSource      srcAudio(clip.getBuffer());
    // AudioSource      srcAudio2(clip2.getBuffer());
    //
    // srcAudio.setVolume(1);
    // srcAudio.setPitch(1);
    // srcAudio2.setPitch(2);
    // srcAudio.setLooping(true);
    // srcAudio.play();
    //
    // char c = ' ';
    // while (c != 'q')
    // {
    //     std::cin >> c;
    //     if (c == 'p')
    //     {
    //         if (srcAudio.isPlaying())
    //             srcAudio.pause();
    //         else
    //             srcAudio.continuePlaying();
    //     }
    //     if (c == 'o')
    //         srcAudio2.play();
    // }
    // srcAudio.Delete();
    // srcAudio2.Delete();
    // AudioListener::DestroyOpenAL();


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
    // Blend Alpha
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    // CullFace
    glCullFace(GL_BACK);
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
    delete BeerEngine::Camera::main;
    BeerEngine::Graphics::Graphics::UnLoad();
    delete window;
    return (0);
}
