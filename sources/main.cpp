#include <thread>
#include "Core/Window.hpp"
#include "Core/Time.hpp"
#include "Core/AScene.hpp"
#include "Core/SceneManager.hpp"
#include "Core/Graphics/Mesh.hpp"
#include "Core/Graphics/ShaderProgram.hpp"

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

    // > TEST
    BeerEngine::Graphics::Mesh mesh(1);
    const glm::vec3 vertPos[] = {
		glm::vec3(0.0f, 0.0f, 0.0f),
		glm::vec3(1.0f, 0.0f, 0.0f),
		glm::vec3(0.0f, 1.0f, 0.0f)
	};
    mesh.add(0, GL_FLOAT, 3, (void *)vertPos, 3);

    BeerEngine::Graphics::ShaderProgram shader(2);
    shader.load(0, GL_VERTEX_SHADER, 
		"#version 330 core\n"
		"layout(location = 0) in vec3 vertexPosition;"
		"void main()"
		"{"
		"   gl_Position = vec4(vertexPosition, 1);"
		"}"
    );
    shader.load(1, GL_FRAGMENT_SHADER,
		"#version 330 core\n"
		"out vec4 outColor;"
        "uniform vec3 color;"
		"void main()"
		"{"
		"    outColor = vec4(color, 1.0);"
		"}"
    );
    shader.compile();
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
        shader.uniform3f("color", 1.0f, 0.0f, 0.0f);
        mesh.render();
        shader.unbind();
    // ! TEST
        window->swapBuffer();
    }
    delete window;
    return (0);
}