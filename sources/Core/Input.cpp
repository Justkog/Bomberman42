#include "Core/Input.hpp"

namespace BeerEngine
{
	std::map<int, int>		Input::mouseButton;
	std::map<int, int>		Input::key;
	glm::vec2				Input::mousePosition;
	glm::vec2				Input::mouseScroll;

	void			Input::SetKey(int keycode, int status)
	{
		key[keycode] = status;
	}

	bool			Input::GetKey(KeyCode keycode)
	{
		return (key[keycode] > 0);
	}

	bool			Input::GetKeyDown(KeyCode keycode)
	{
		return (key[keycode] == 1);
	}

	bool			Input::GetKeyUp(KeyCode keycode)
	{
		return (key[keycode] == 0);
	}

	void			Input::SetMouseButton(int button, int status)
	{
		mouseButton[button] = status;
	}

	bool			Input::GetMouseButton(int button)
	{
		return (mouseButton[button] > 0);
	}

	bool			Input::GetMouseButtonDown(int button)
	{
		return (mouseButton[button] == 1);
	}

	bool			Input::GetMouseButtonUp(int button)
	{
		return (mouseButton[button] == 0);
	}

}