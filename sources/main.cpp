#include <thread>
#include <chrono>

#define NK_INCLUDE_FIXED_TYPES
#define NK_INCLUDE_STANDARD_IO
#define NK_INCLUDE_STANDARD_VARARGS
#define NK_INCLUDE_DEFAULT_ALLOCATOR
#define NK_INCLUDE_VERTEX_BUFFER_OUTPUT
#define NK_INCLUDE_FONT_BAKING
#define NK_INCLUDE_DEFAULT_FONT
#define NK_IMPLEMENTATION
#define NK_GLFW_GL3_IMPLEMENTATION

#include "Core/BeerEngine.hpp"
#include "Game/SceneTest.hpp"
#include "Game/Assets.hpp"


static int      frameCount = 0;
static int      FPS = 60;
static int      UPS = 60;

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
// #ifdef BE_DEBUG
//             std::cout << "FPS: " << frameCount << " - UPS: " << fixeUpdateNumber << std::endl;
// #endif
            FPS = frameCount;
            UPS = fixeUpdateNumber;
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
    // Nukclear
    struct nk_context *ctx;
    ctx = nk_glfw3_init(window->getWindow(), NK_GLFW3_INSTALL_CALLBACKS);
    struct nk_font_atlas *atlas;
    nk_glfw3_font_stash_begin(&atlas);

    nk_glfw3_font_stash_end();

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
    // FPS
    while (!window->isClose())
    {
        window->update();
        scene = BeerEngine::SceneManager::GetCurrent();
        nk_glfw3_new_frame();


        if (nk_begin(ctx, "Debug Info", nk_rect(10, 10, 220, 80), NK_WINDOW_BORDER | NK_WINDOW_MOVABLE | NK_WINDOW_CLOSABLE))
        {
            std::stringstream ss;
            ss << "FPS: " << FPS << " / UPS: " << UPS;
            nk_layout_row_dynamic(ctx, 20, 1);
            nk_label(ctx, ss.str().c_str(), NK_TEXT_LEFT);
        }    
        nk_end(ctx);

        // Draw
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LESS);
        glEnable(GL_CULL_FACE);
        glCullFace(GL_BACK);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        window->clear();
        if (scene != nullptr)
        {
            scene->mutexLock(true);
            scene->renderUpdate();
            scene->render();
            scene->renderUI(ctx);
            scene->mutexLock(false);
        }
        glDisable(GL_DEPTH_TEST);
        nk_glfw3_render(NK_ANTI_ALIASING_ON, MAX_VERTEX_BUFFER, MAX_ELEMENT_BUFFER);
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
