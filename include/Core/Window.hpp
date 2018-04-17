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
		glm::mat4       _perspective;
		glm::mat4       _ortho;
		Window(std::string title, int width, int height);

		static Window	*_Instance;
	public:
		~Window();
		GLFWwindow      *getWindow(void);
		void            clear(void);
		void            swapBuffer(void);
		glm::mat4       &getProjection3D(void);
		glm::mat4       &getProjection2D(void);

		static Window   *CreateWindow(std::string title, int width, int height);
		static Window	*GetInstance(void);
	};
}

#endif