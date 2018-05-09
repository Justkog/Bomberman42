#include "Core/Window.hpp"
#include "Core/Input.hpp"

namespace BeerEngine
{
	Window	*Window::_Instance = nullptr;
	Window::Window(std::string title, int width, int height) :
		_title(title), _width(width), _height(height), _windowWidth(width), _windowHeight(height)
	{
		_window = glfwCreateWindow(_width, _height, _title.c_str(), NULL, NULL);
		_perspective = glm::perspective(glm::radians(60.0f), (float)_width / (float)_height, 0.01f, 1000.0f);
		_ortho = glm::ortho(0.0f, (float)_width, 0.0f, (float)_height);
		_close = false;
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

	void            Window::update(void)
	{
		// BeerEngine::Input::Update();
		glfwPollEvents();
	}

	void            Window::swapBuffer(void)
	{
		glfwSwapBuffers(_window);
	}

	GLFWwindow      *Window::getWindow(void)
	{
		return (_window);
	}

	glm::mat4       &Window::getProjection3D(void)
	{
		return (_perspective);
	}

	glm::mat4       &Window::getProjection2D(void)
	{
		return (_ortho);
	}


	void			Window::closeRequest(void)
	{
		_close = true;
	}

	bool			Window::isClose(void)
	{
		return (glfwWindowShouldClose(_window) || _close);
	}

	void			Window::setWindowProperties(int x, int y, int width, int height)
	{
		_xPos = x;
		_yPos = y;
		_windowWidth = width;
		_windowHeight = height;
		_width = width;
		_height = height;
	}

	static void     win_resize_callback(GLFWwindow *window, int width, int height)
	{
		// std::cout << "FramebufferSizeCallback" << std::endl;
		static const float aspect = 16.0f / 9.0f;
		Window  *win = (Window *)glfwGetWindowUserPointer(window);
		// if (win)
		// {
		// 	float a = (float)width / (float)height;
		// 	int minX = 0;
		// 	int minY = 0;
		// 	int maxX = width;
		// 	int maxY = height;
		// 	if (a < aspect)
		// 	{
		// 		maxY = (int)std::round((float)width * 9.0f / 16.0f);
		// 		minY = (height - maxY) / 2;
		// 	}
		// 	else if (a > aspect)
		// 	{
		// 		maxX = (int)std::round((float)height * 16.0f / 9.0f);
		// 		minX = (width - maxX) / 2;
		// 	}
		// 	glViewport(minX, minY, maxX, maxY);
		// }
		glViewport(0, 0, width, height);
		if (glfwGetWindowMonitor(window) != nullptr) // full screen is set
			return;
		int x, y;
		glfwGetWindowPos(window, &x, &y);
		Window::GetInstance()->setWindowProperties(x, y, width, height);
	}

	static void     win_key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		(void)window;
		// std::cout << "Key: " << key << ", action: " << action << std::endl;
		Input::SetKey(key, action);
	}

	static void     win_cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
	{
		static float lastXpos = xpos;
		static float lastYpos = ypos;
		(void)window;
		BeerEngine::Input::mousePosition[0] = xpos;
		BeerEngine::Input::mousePosition[1] = ypos;
		BeerEngine::Input::SetAxis("Mouse X", xpos - lastXpos);
		BeerEngine::Input::SetAxis("Mouse Y", ypos - lastYpos);
		lastXpos = xpos;
		lastYpos = ypos;
	}

	static void     win_mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
	{
		(void)window;
		// std::cout << "Button: " << button << ", action: " << action << std::endl;
		Input::SetMouseButton(button, action);
	}

	static void     win_scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
	{
		(void)window;
		BeerEngine::Input::mouseScroll[0] = xoffset;
		BeerEngine::Input::mouseScroll[1] = yoffset;
	}

	static void		window_focus_callback(GLFWwindow* window, int focused)
	{
		if (focused)
		{
			std::cout << "The window gained input focus" << std::endl;
		}
		else
		{
			std::cout << "The window lost input focus" << std::endl;
		}
	}

	Window          *Window::CreateWindow(std::string title, int width, int height)
	{
		if (_Instance != nullptr)
			return (_Instance);
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
			// glfwWindowHint(GLFW_FOCUSED, GLFW_TRUE);
			glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
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
				glfwSetFramebufferSizeCallback(win->getWindow(), win_resize_callback);
				glfwSetKeyCallback(win->getWindow(), win_key_callback);
				glfwSetCursorPosCallback(win->getWindow(), win_cursor_position_callback);
				glfwSetMouseButtonCallback(win->getWindow(), win_mouse_button_callback);
				glfwSetScrollCallback(win->getWindow(), win_scroll_callback);
				glfwGetWindowPos(win->getWindow(), win->getXPos(), win->getYPos());
				glfwSetWindowFocusCallback(win->getWindow(), window_focus_callback);
				glfwSwapInterval(0);
				glewExperimental = true;
				if (glewInit() != GLEW_OK)
				{
					delete win;
					win = nullptr;
					std::cout << "Failed to initialize GLEW\n";
				}
			}
		}
		_Instance = win;
		return (win);
	}

	Window	*Window::GetInstance(void)
	{
		return (_Instance);
	}

	int		*Window::getXPos()
	{
		return &this->_xPos;
	}

	int		*Window::getYPos()
	{
		return &this->_yPos;
	}

	int		Window::getWidth()
	{
		return _width;
	}

	int		Window::getHeight()
	{
		return _height;
	}

	int		Window::getWindowedWidth()
	{
		return _windowWidth;
	}

	int		Window::getWindowedHeight()
	{
		return _windowHeight;
	}

	void	Window::setFullScreen(void)
	{
		auto monitor = glfwGetPrimaryMonitor();
		auto videoMode = glfwGetVideoMode(monitor);
		glfwSetWindowSizeCallback(_window, nullptr);
		glfwGetWindowPos(_window, &_xPos, &_yPos);
		_width = videoMode->width;
		_height = videoMode->height;
		// std::cout << "Set full screen at " << videoMode->width << " * " << videoMode->height <<  std::endl;
		glfwSetWindowMonitor(_window, monitor, 0, 0, _width, _height, videoMode->refreshRate);
	}

	// call back used to force a resize after coming back from full screen mode due to a bug on macos
	void Window::CallbackResize(GLFWwindow* window, int cx, int cy)
	{
		// std::cout << "SetWindowSizeCallback" << std::endl;
		glfwSetWindowSize(window, GetInstance()->getWidth(), GetInstance()->getHeight());
		glfwSetWindowPos(window, *GetInstance()->getXPos(), *GetInstance()->getYPos());
		glfwSetWindowSizeCallback(window, nullptr);
	}

	void	Window::setWindowed(void)
	{
		auto monitor = glfwGetPrimaryMonitor();
		auto videoMode = glfwGetVideoMode(monitor);
		glfwSetWindowSizeCallback(_window, Window::CallbackResize);
		_width = _windowWidth;
		_height = _windowHeight;
		// std::cout << "setting windowed x = " << _xPos << " / y = " << _yPos << " / width = " << WINDOW_WIDTH << std::endl;
		glfwSetWindowMonitor(_window, NULL, _xPos, _yPos, _width, _height, videoMode->refreshRate);
	}

	void Window::resize(int width, int height)
	{
		// std::cout << "resizing window" << std::endl;
		_windowWidth = width;
		_windowHeight = height;
		if (glfwGetWindowMonitor(_window) != nullptr) // full screen is set
			return;
		_width = _windowWidth;
		_height = _windowHeight;
		glfwSetWindowSize(_window, _width, _height);
	}

	bool Window::isFullScreen()
	{
		return (glfwGetWindowMonitor(_window) != nullptr);
	}

}