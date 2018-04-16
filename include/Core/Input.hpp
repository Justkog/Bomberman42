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
		static std::map<int, int>	mouseButton;
		static std::map<int, int>	key;

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
	};
}

#endif