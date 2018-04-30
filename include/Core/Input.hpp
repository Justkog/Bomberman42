#ifndef BE_CORE_INPUT_HPP
#define BE_CORE_INPUT_HPP 1

#include <map>
#include "Core.hpp"
#include "KeyCode.hpp"

namespace BeerEngine
{
	class Input
	{
	private:
		static std::map<int, int>			mouseButton;
		static std::map<int, int>			key;
		static std::map<std::string, float> axis;

	public:
		static glm::vec2	mousePosition;
		static glm::vec2	mouseScroll;
		static void			SetKey(int keycode, int status);
		static bool			GetKey(KeyCode keycode);
		static bool			GetKeyDown(KeyCode keycode);
		static bool			GetKeyUp(KeyCode keycode);
		static void			SetMouseButton(int mouseButton, int status);
		static bool			GetMouseButton(int mouseButton);
		static bool			GetMouseButtonDown(int mouseButton);
		static bool			GetMouseButtonUp(int mouseButton);
		static void			SetAxis(std::string name, float value);
		static float		GetAxis(std::string name);

		static void			Update(void);
	};
}

#endif