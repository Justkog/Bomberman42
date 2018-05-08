#ifndef BE_CORE_GAMEOBJECT_HPP
#define BE_CORE_GAMEOBJECT_HPP 1

#include "Core/Core.hpp"
#include "Core/AScene.hpp"
#include "Core/Transform.hpp"
// #include "Core/Component/Component.hpp"
#include "Core/Component/IStart.hpp"
#include "Core/Json/JsonSerializable.hpp"

struct nk_font;

namespace BeerEngine
{
    class GameObject : public JsonSerializable, public JsonDeserializable
	{
	protected:
		std::vector<Component::Component *> _components;
		std::vector<Component::Component *> _toStart;
		std::vector<Component::Component *> _toStartUI;
		std::vector<Component::Component *> _toDestroy;

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
        virtual void    startUI(struct nk_context *ctx, std::map<std::string, nk_font *> fonts);
        virtual void    renderUI(struct nk_context *ctx);

		void    destroy(Component::Component *comp);
		void    destroyComponent(void);
		void    destroy(GameObject *go);

		template<typename T, typename std::enable_if<std::is_base_of<GameObject, T>::value>::type* = nullptr>
		T	*instantiate(void)
		{
			return (_scene.instantiate<T>());
		}

		template<typename T, typename std::enable_if<std::is_base_of<GameObject, T>::value>::type* = nullptr>
		T	*instantiate(std::string prefabPath)
		{
			return (_scene.instantiate<T>(prefabPath));
		}

        template<typename T, typename std::enable_if<std::is_base_of<Component::Component, T>::value>::type* = nullptr>
		T	*AddComponent(void)
		{
			T *c = new T(this);
			registerComponent(c);
			return (c);
		}

		void	registerComponent(Component::Component *comp)
		{
			_components.push_back(comp);
			_toStart.push_back(comp);
			_toStartUI.push_back(comp);
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
        void    componentRenderAlpha(void);
        void    componentPhysicUpdate(void);
        void    componentStartUI(struct nk_context *ctx, std::map<std::string, nk_font *> fonts);
        void    componentRenderUI(struct nk_context *ctx);

		std::vector<Component::Component *> GetComponents(void);

		virtual nlohmann::json	serialize();
        virtual void deserialize(const nlohmann::json & j);
		static GameObject * Deserialize(const nlohmann::json & j, AScene & scene);

		void save(std::string filePath);
        void load(std::string filePath);
	};
}

#endif