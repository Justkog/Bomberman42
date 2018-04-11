#ifndef BE_CORE_WINDOW_HPP
#define BE_CORE_WINDOW_HPP 1

#include "Core.hpp"

namespace BeerEngine
{
    class Window
    {
    private:
        std::string     _title;
        int             _width;
        int             _height;
        GLFWwindow      *_window;
        Window(std::string title, int width, int height);

    public:
        ~Window();
        GLFWwindow      *getWindow(void);
        void            clear(void);
        void            swapBuffer(void);

        static Window   *CreateWindow(std::string title, int width, int height);
    };
}

#endif