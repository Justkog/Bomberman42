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
		Maths::Matrix4x4       _perspective;
		Maths::Matrix4x4       _ortho;
		bool			_close;
		Window(std::string title, int width, int height);

		static Window	*_Instance;
	public:
		~Window();
		GLFWwindow      *getWindow(void);
		void            clear(void);
		void            swapBuffer(void);
		Maths::Matrix4x4       &getProjection3D(void);
		Maths::Matrix4x4       &getProjection2D(void);
		void			closeRequest(void);
		bool			isClose(void);

		static Window   *CreateWindow(std::string title, int width, int height);
		static Window	*GetInstance(void);
	};
}

#endif