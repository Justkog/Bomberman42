#ifndef BE_CORE_GAMEOBJECT_HPP
#define BE_CORE_GAMEOBJECT_HPP 1

#include <vector>

namespace BeerEngine
{
	namespace Component
	{
		class Component;
	}

    class GameObject
	{
	protected:
		int		_uniqueID;
		std::vector<Component::Component *> _components;

	public:
		GameObject(int uniqueID);
		~GameObject(void);

        template<typename T, typename std::enable_if<std::is_base_of<Component::Component, T>::value>::type* = nullptr>
		T	*AddComponent(void)
		{
			T *c = new T(this);
			_components.push_back(c);
			return (c);
		}

		template<typename T, typename std::enable_if<std::is_base_of<Component::Component, T>::value>::type* = nullptr>
		T	*GetComponent(void)
		{
			for (Component::Component *c : _components)
			{
				if (T *r = dynamic_cast<T *>(c))
					return (r);
			}
			return (nullptr);
		}

	};
}

#endif