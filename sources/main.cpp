#include <thread>
#include "Core/Window.hpp"
#include "Core/Time.hpp"
#include "Core/AScene.hpp"
#include "Core/SceneManager.hpp"
#include "Core/Graphics/Mesh.hpp"
#include "Core/Graphics/MeshBuilder.hpp"
#include "Core/Graphics/ShaderProgram.hpp"
#include "Core/Graphics/Graphics.hpp"
#include "Core/IO/FileUtils.hpp"
#include "Core/Transform.hpp"

#include "Game/SceneTest.hpp"

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
                scene->fixedUpdate();
            fixeUpdateNumber++;
            fixedTimer -= fixedUpdateTime;
        }
        if (scene != nullptr)
            scene->update();
        if (timer >= 1.0)
        {
            // #ifdef BE_DEBUG
            // std::cout << "Fixed Update Number: " << fixeUpdateNumber << std::endl;
            // std::cout << "FPS: " << frameCount << std::endl;
            // #endif
            std::cout << "FPS: " << frameCount << " - UPS: " << fixeUpdateNumber << std::endl;

            fixeUpdateNumber = 0;
            frameCount = 0;
            timer -= 1.0;
        }
    }
    std::cout << "Thread Update: Finish" << std::endl;
}

int main(void)
{
    std::srand(std::time(nullptr));
    BeerEngine::Window *window = BeerEngine::Window::CreateWindow("Bomberman", 1280, 720);
    BeerEngine::AScene  *scene;

    std::thread updateLoop (updateThread, window);
    updateLoop.detach();

    BeerEngine::Graphics::Graphics::Load();
    BeerEngine::SceneManager::LoadScene<SceneTest>();
    // > TEST
    BeerEngine::Graphics::ShaderProgram shader(2);
    shader.load(0, GL_VERTEX_SHADER,
        BeerEngine::IO::FileUtils::LoadFile("shaders/ui.vs").c_str()
	);
    shader.load(1, GL_FRAGMENT_SHADER,
        BeerEngine::IO::FileUtils::LoadFile("shaders/ui.fs").c_str()
	);
    shader.compile();
    BeerEngine::Graphics::Mesh mesh(1);
    const float vertPos[] = {
		0.0f, 0.0f,
		1.0f, 0.0f,
		0.0f, 1.0f,
	};
	mesh.add(0, GL_FLOAT, 2, (void *)vertPos, 3);
    // glm::quat viewRotate = glm::quat(glm::vec3(glm::radians(0.0f), glm::radians(0.0f), 0.0f));
    // glm::mat4 viewMat = glm::translate(glm::toMat4(viewRotate), glm::vec3(0.0f, -1.0f, -0.0f));

    // BeerEngine::Transform planeTransform;
    // planeTransform.position = glm::vec3(0.0f, 0.0f, 4.0f);
    // planeTransform.rotation = glm::quat(glm::vec3(glm::radians(0.0f), glm::radians(-22.5f), glm::radians(0.0f)));
    // glm::mat4 planeMat = planeTransform.getMat4();

    // BeerEngine::Transform cubeTransform;
    // cubeTransform.parent = &planeTransform;
    // cubeTransform.position = glm::vec3(0.0f, 0.0f, 0.0f);
    // cubeTransform.rotation = glm::quat(glm::vec3(glm::radians(0.0f), glm::radians(-22.5f), glm::radians(0.0f)));
    // cubeTransform.scale = glm::vec3(1.5f, 0.5f, 1.5f);
    // glm::mat4 cubeMat = cubeTransform.getMat4();

    // glm::vec3 lightDir;
    // ! TEST

    // depth-testing
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    // CullFace
    glCullFace(GL_BACK);
    glEnable(GL_CULL_FACE);
    // FPS
    while (!glfwWindowShouldClose(window->getWindow()))
    {
        window->clear();
        scene = BeerEngine::SceneManager::GetCurrent();
        if (scene != nullptr)
        {
            scene->renderUpdate();
            scene->render();
        }
    // > TEST
        shader.bind();
        mesh.render();
        // shader.uniformMat("projection", window->getProjection3D());
        // shader.uniformMat("view", viewMat);
        // shader.uniformMat("model", planeMat);

        // double time = glfwGetTime();
        // lightDir = glm::normalize(glm::vec3(0.5f, 1, 1));
        
        // shader.uniform3f("lightDir", lightDir);
        // shader.uniform3f("color", 0.75f, 0.75f, 0.75f);
        // BeerEngine::Graphics::Graphics::plane->render();

        // shader.uniformMat("model", cubeMat);
        // shader.uniform3f("color", 0.f, 0.75f, 0.75f);
        // BeerEngine::Graphics::Graphics::cube->render();
        
        shader.unbind();
    // ! TEST
        window->swapBuffer();
        frameCount++;
    }
    BeerEngine::Graphics::Graphics::UnLoad();
    delete window;
    return (0);
}