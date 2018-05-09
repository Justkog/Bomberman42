#include "Core/Input.hpp"

namespace BeerEngine
{
	std::map<int, int>		Input::mouseButton;
	std::map<int, int>		Input::key;
	std::map<std::string, float>		Input::axis;
	glm::vec2				Input::mousePosition;
	glm::vec2				Input::mouseScroll;

	std::function<void (int)> Input::onKeyPushedDefault()
	{
		return [] (int i) { };
	}

	std::function<void (int)>	Input::onKeyPushed = Input::onKeyPushedDefault();

	void			Input::SetKey(int keycode, int status)
	{
		key[keycode] = status;
		if (status == 1)
			onKeyPushed(keycode);
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

	int				Input::GetKeyStatus(KeyCode keycode)
	{
		return (key[keycode]);
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

	void			Input::SetAxis(std::string name, float value)
	{
		axis[name] = value;
	}

	float			Input::GetAxis(std::string name)
	{
		return (axis[name]);
	}

	void			Input::Update(void)
	{
		for (std::map<std::string, float>::iterator it = axis.begin(); it != axis.end(); ++it)
		{
			it->second = 0.0f;
		}
		for (std::map<int, int>::iterator it = key.begin(); it != key.end(); ++it)
		{
			if (it->second == 1)
				it->second = 2;
		}
		for (std::map<int, int>::iterator it = mouseButton.begin(); it != mouseButton.end(); ++it)
		{
			if (it->second == 1)
				it->second = 2;
		}
	}

}