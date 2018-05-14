#ifndef BE_CORE_COMPONENT_HPP
#define BE_CORE_COMPONENT_HPP 1

#include "Core/Core.hpp"
#include "Core/Json/JsonSerializable.hpp"
#include "Core/GameObject.hpp"

namespace BeerEngine
{
	namespace Component
	{
		typedef std::map<std::string, Component*(*)(GameObject *)> add_component_type;

		class Component : public JsonSerializable, public SigSlotBase
		{
		protected:
		public:

			Component(GameObject *gameObject);
			virtual ~Component(void) {}

			void    destroy(GameObject *go = nullptr);

			GameObject		*_gameObject;
			bool			_isActive;

			void	setActive(bool state);

			template<typename T>
			static Component * createInstance(GameObject *gameObject)
			{ 
				return new T(gameObject); 
			}

			template<typename T>
			static Component * addComponent(GameObject *gameObject)
			{ 
				return (gameObject->AddComponent<T>()); 
			}

			virtual nlohmann::json	serialize();
			virtual void deserialize(const nlohmann::json & j, BeerEngine::JsonLoader & loader);
			static Component * Deserialize(const nlohmann::json & j, BeerEngine::JsonLoader & loader, GameObject *go);

			static add_component_type typeToAddComponent;
			static add_component_type createAddMap();
		};
	}
}

#endif