#ifndef BE_CORE_GAMEOBJECT_HPP
#define BE_CORE_GAMEOBJECT_HPP 1

#include "Core/Core.hpp"
#include "Core/Transform.hpp"
#include "Core/Component/Component.hpp"
#include "Core/Component/MeshRenderer.hpp"
#include "Core/Json/JsonSerializable.hpp"

namespace BeerEngine
{
    class GameObject : public JsonSerializable, public JsonDeserializable
	{
	protected:
		std::vector<Component::Component *> _components;

	public:
		int			_uniqueID;
		AScene		&_scene;
		Transform	transform;
		std::string	name;

		// GameObject() {}
		// GameObject(int uniqueID);
		GameObject(int uniqueID, AScene &scene);

		virtual ~GameObject(void);

		int				getID();

		virtual void	start(void);
		virtual void    fixedUpdate(void);
        virtual void    update(void);
        virtual void    renderUpdate(void);
        virtual void    render(void);

		void    destroy(GameObject *go);

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

		std::vector<Component::Component *> GetComponents(void);

		virtual nlohmann::json	serialize();
        // virtual void deserialize(const nlohmann::json & j);
		static GameObject * Deserialize(const nlohmann::json & j, AScene & scene);
	};
}

#endif