#include "Core/Window.hpp"
#include "Core/Input.hpp"

namespace BeerEngine
{
	Window	*Window::_Instance = nullptr;
	Window::Window(std::string title, int width, int height) :
		_title(title), _width(width), _height(height)
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


	static void     win_resize_callback(GLFWwindow *window, int width, int height)
	{
		static const float aspect = 16.0f / 9.0f;
		Window  *win = (Window *)glfwGetWindowUserPointer(window);
		if (win)
		{
			float a = (float)width / (float)height;
			int minX = 0;
			int minY = 0;
			int maxX = width;
			int maxY = height;
			if (a < aspect)
			{
				maxY = (int)std::round((float)width * 9.0f / 16.0f);
				minY = (height - maxY) / 2;
			}
			else if (a > aspect)
			{
				maxX = (int)std::round((float)height * 16.0f / 9.0f);
				minX = (width - maxX) / 2;
			}
			glViewport(minX, minY, maxX, maxY);
		}
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
}