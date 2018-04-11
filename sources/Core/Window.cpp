#include "Core/Window.hpp"

namespace BeerEngine
{
    Window::Window(std::string title, int width, int height) :
        _title(title), _width(width), _height(height)
    {
        _window = glfwCreateWindow(_width, _height, _title.c_str(), NULL, NULL);
    }

    Window::~Window()
    {
        if (_window != NULL)
        {
            glfwDestroyWindow(_window);
            _window = NULL;
        }
        glfwTerminate();
    }

    void            Window::clear(void)
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void            Window::swapBuffer(void)
    {
        glfwSwapBuffers(_window);
        glfwPollEvents();
    }

    GLFWwindow      *Window::getWindow(void)
    {
        return (_window);
    }

    Window          *Window::CreateWindow(std::string title, int width, int height)
    {
        Window  *win = nullptr;

        if (!glfwInit())
            std::cout << "Failed to initialize GLFW\n";
        else
        {
            glfwWindowHint(GLFW_SAMPLES, 4);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
            glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
            glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
            glfwWindowHint(GLFW_DEPTH_BITS, 32);
            win = new Window(title, width, height);
            if (win->getWindow() == NULL)
            {
                delete win;
                win = nullptr;
                std::cout << "Failed to open GLFW window. If you have an Intel GPU, they are not 4.1 compatible.\n";
            }
            else
            {
                glfwMakeContextCurrent(win->getWindow());
                glfwSetWindowUserPointer(win->getWindow(), win);
                glfwSwapInterval(0);
                glewExperimental=true;
                if (glewInit() != GLEW_OK)
                {
                    delete win;
                    win = nullptr;
                    std::cout << "Failed to initialize GLEW\n";
                }
            }
        }
        return (win);
    }
}