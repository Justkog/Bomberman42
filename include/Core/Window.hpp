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
		int				_xPos;
		int 			_yPos;
		int 			_windowWidth;
		int 			_windowHeight;
		GLFWwindow      *_window;
		glm::mat4       _perspective;
		glm::mat4       _ortho;
		bool			_close;
		Window(std::string title, int width, int height);

		static Window	*_Instance;
	public:
		~Window();
		GLFWwindow      *getWindow(void);
		int     		*getXPos(void);
		int     		*getYPos(void);
		int				getWidth();
		int				getHeight();
		void			setWindowProperties(int x, int y, int width, int height);
		void            clear(void);
		void            update(void);
		void            swapBuffer(void);
		glm::mat4       &getProjection3D(void);
		glm::mat4       &getProjection2D(void);
		void			closeRequest(void);
		bool			isClose(void);
		void			setFullScreen(void);
		void			setWindowed(void);
		void			resize(int width, int height);

		static Window   *CreateWindow(std::string title, int width, int height);
		static Window	*GetInstance(void);

		static void CallbackResize(GLFWwindow* window, int cx, int cy);

	};
}

#endif