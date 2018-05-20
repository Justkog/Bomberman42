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

#define MAX_VERTEX_BUFFER 512 * 1024
#define MAX_ELEMENT_BUFFER 128 * 1024

#include "Core/Core.hpp"
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Core/BeerEngine.hpp"
#include "Game/SceneMain.hpp"
#include "Game/Assets.hpp"
//#include <nuklear.h>

static int      frameCount = 0;
static int      FPS = 60;
static int      UPS = 60;

void updateThread(BeerEngine::Window *window)
{
    static const double fixedUpdateTime = 1.0 / 60.0;
    double  fixedTimer = 0.0;
    double  timer = 0.0;
    int     fixeUpdateNumber = 0;
    BeerEngine::AScene  *scene = nullptr;
    std::cout << "Thread Update: Started" << std::endl;
    while (!window->isClose())
    {
        scene = BeerEngine::SceneManager::GetCurrent(false);

        if (scene != nullptr)
        {
            scene->mutexLock(true);
            scene->start();
            scene->mutexLock(false);
        }
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
        // if (BeerEngine::Input::GetKeyDown(BeerEngine::KeyCode::ESCAPE))
        //     window->closeRequest();
        if (scene != nullptr)
        {
            scene->mutexLock(true);
            scene->update();
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

		// BeerEngine::Input::Update();
		std::this_thread::sleep_for(std::chrono::milliseconds(1));
		// std::cout << "update thread" << std::endl;
    }
    std::cout << "Thread Update: Finish" << std::endl;
}

int main(void)
{
    std::srand(std::time(nullptr));
    BeerEngine::Window  *window = BeerEngine::Window::CreateWindow("Bomberman", WINDOW_WIDTH, WINDOW_HEIGHT);
    BeerEngine::AScene  *scene;
    // Nuklear
    struct nk_context *ctx;
    ctx = nk_glfw3_init(window->getWindow(), NK_GLFW3_INSTALL_CALLBACKS);

	std::map<std::string, nk_font *> fonts;
    struct nk_font_atlas *atlas;
    nk_glfw3_font_stash_begin(&atlas);

	struct nk_font_config cfg = nk_font_config(13);
	cfg.pixel_snap = true;
	fonts["main"] = nk_font_atlas_add_from_file(atlas, "assets/fonts/Capture_it.ttf", 48, &cfg);
	fonts["smallMain"] = nk_font_atlas_add_from_file(atlas, "assets/fonts/Capture_it.ttf", 26, &cfg);
	fonts["bigMain"] = nk_font_atlas_add_from_file(atlas, "assets/fonts/Capture_it.ttf", 128, &cfg);
	fonts["secondary"] = nk_font_atlas_add_from_file(atlas, "assets/fonts/SEASRN__.ttf", 80, &cfg);

	fonts["default"] = nk_font_atlas_add_default(atlas, 13.0f, 0);

    nk_glfw3_font_stash_end();
	nk_style_set_font(ctx, &fonts["default"]->handle);
    // Audio
    BeerEngine::Audio::AudioListener::Load();
    // Graphics
    BeerEngine::Graphics::Graphics::Load();
    // Game Assets
    Assets::GetInstance()->load();
    // First Scene
    // BeerEngine::SceneManager::LoadScene<SceneRandom>();
    BeerEngine::SceneManager::LoadScene<SceneMain>();
    // BeerEngine::SceneManager::LoadScene("main.scene");

    // Thread Update
    std::thread updateLoop (updateThread, window);
    updateLoop.detach();
    // FPS
    // glfwFocusWindow(window->getWindow());
	glfwShowWindow(window->getWindow());

    while (!window->isClose())
    {
        window->update();

		// if scene changes, it has to be loaded in this thread
		// it needs to set a variable to a specific value and wait
		// so that the other thread detects it and also sets another variable to a specific value and wait
		// once this value has changed this thread changes the scene and reset the variable
		// so that the other thread can stop waiting
        scene = BeerEngine::SceneManager::GetCurrent(true);

        nk_glfw3_new_frame();

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
            scene->startUI(ctx, fonts);
            scene->renderUI(ctx);
            scene->destroyGameObjects();
            scene->mutexLock(false);
        }
        glDisable(GL_DEPTH_TEST);

		if (nk_begin(ctx, "Debug Info", nk_rect(10, 10, 220, 80), NK_WINDOW_BORDER | NK_WINDOW_MOVABLE | NK_WINDOW_MINIMIZABLE | NK_WINDOW_CLOSABLE))
        {
            std::stringstream ss;
            ss << "FPS: " << FPS << " / UPS: " << UPS;
            nk_layout_row_dynamic(ctx, 20, 1);
            nk_label(ctx, ss.str().c_str(), NK_TEXT_LEFT);
        }
        nk_end(ctx);

        nk_glfw3_render(NK_ANTI_ALIASING_ON, MAX_VERTEX_BUFFER, MAX_ELEMENT_BUFFER);
		BeerEngine::Input::Update();
        window->swapBuffer();
        frameCount++;
		// std::cout << "render thread" << std::endl;
    }
    nk_glfw3_shutdown();
    // srcAudio.Delete();
    // srcAudio2.Delete();
    BeerEngine::Audio::AudioListener::DestroyOpenAL();
    delete BeerEngine::Camera::main;
    Assets::GetInstance()->unload();
    delete Assets::GetInstance();
    BeerEngine::Graphics::Graphics::UnLoad();
    delete window;
    return (0);
}
