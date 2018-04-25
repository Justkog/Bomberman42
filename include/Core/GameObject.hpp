#ifndef BE_CORE_GAMEOBJECT_HPP
#define BE_CORE_GAMEOBJECT_HPP 1

#include <vector>
#include "Transform.hpp"

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
		Transform	transform;
		std::string	name;

		GameObject(int uniqueID);
		virtual ~GameObject(void);

		virtual void	start(void);
		virtual void    fixedUpdate(void);
        virtual void    update(void);
        virtual void    renderUpdate(void);
        virtual void    render(void);

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

		template<typename T, typename std::enable_if<std::is_base_of<Component::Component, T>::value>::type* = nullptr>
		std::vector<T *>	GetComponents(void)
		{
			std::vector<T *> res;
			for (Component::Component *c : _components)
			{
				if (T *r = dynamic_cast<T *>(c))
					res.push_back(r);
			}
			return res;
		}

		void    componentStart(void);
		void    componentFixedUpdate(void);
        void    componentUpdate(void);
        void    componentRenderUpdate(void);
        void    componentRender(void);
        void    componentPhysicUpdate(void);

		std::vector<Component::Component *> GetComponents(void)
		{
			return _components;
		}

	};
}

#endif