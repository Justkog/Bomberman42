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

    BeerEngine::Graphics::Graphics::Load();

    // > TEST
    BeerEngine::Graphics::MeshBuilder meshBuilder;
    meshBuilder.addVertice(glm::vec3(0.0f, 0.0f, 0.0f))
        .addVertice(glm::vec3(1.0f, 0.0f, 0.0f))
        .addVertice(glm::vec3(0.0f, 1.0f, 0.0f))
        .addVertice(glm::vec3(0.0f, 1.0f, 0.0f))
        .addVertice(glm::vec3(1.0f, 0.0f, 0.0f))
        .addVertice(glm::vec3(1.0f, 1.0f, 0.0f));
    BeerEngine::Graphics::Mesh *mesh = meshBuilder.build();

    BeerEngine::Graphics::ShaderProgram shader(2);
    shader.load(0, GL_VERTEX_SHADER,
        BeerEngine::IO::FileUtils::LoadFile("shaders/basic.vs").c_str()
	);
    shader.load(1, GL_FRAGMENT_SHADER,
        BeerEngine::IO::FileUtils::LoadFile("shaders/basic.fs").c_str()
	);
    shader.compile();
    glm::quat viewRotate = glm::quat(glm::vec3(0.0f, glm::radians(0.0f), 0.0f));
    glm::mat4 viewMat = glm::translate(glm::toMat4(viewRotate), glm::vec3(0.0f, -0.5f, 0.0f));
    BeerEngine::Transform modelTransform;
    modelTransform.pivot = glm::vec3(0.5f, 0.5f, 0.0f);
    modelTransform.rotation = glm::quat(glm::vec3(glm::radians(45.f), glm::radians(45.f), 0.0f));
    modelTransform.position = glm::vec3(0.0f, 0.0, 4.0f);
    glm::mat4 modelMat = modelTransform.getMat4();
    glm::mat4 identityMat = glm::translate(glm::vec3(0.0f, 0.0f, -4.0f));
    // ! TEST

    // depth-testing
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    // CullFace
    glCullFace(GL_BACK);
    glEnable(GL_CULL_FACE);
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
        shader.uniformMat("projection", window->getProjection3D());
        shader.uniformMat("view", viewMat);
        shader.uniformMat("model", modelMat);
        shader.uniform3f("color", 0.75f, 0.0f, 0.0f);
        mesh->render();
        shader.uniformMat("model", identityMat);
        shader.uniform3f("color", 0.75f, 0.75f, 0.75f);
        BeerEngine::Graphics::Graphics::plane->render();
        shader.unbind();
    // ! TEST
        window->swapBuffer();
    }
    BeerEngine::Graphics::Graphics::UnLoad();
    delete window;
    return (0);
}