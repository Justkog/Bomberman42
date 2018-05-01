#ifndef BE_CORE_COMPONENT_HPP
#define BE_CORE_COMPONENT_HPP 1

#include "Core/Core.hpp"
#include "Core/Json/JsonSerializable.hpp"


namespace BeerEngine
{
	namespace Component
	{
		typedef std::map<std::string, Component*(*)(GameObject *)> component_type;

		class Component : public JsonSerializable
		{
		protected:
		public:
			Component(GameObject *gameObject);
			virtual ~Component(void) {}

			void    destroy(GameObject *go = nullptr);

			GameObject		*_gameObject;

			virtual nlohmann::json	serialize();

			template<typename T>
			static Component * createInstance(GameObject *gameObject)
			{ 
				return new T(gameObject); 
			}

			virtual void deserialize(const nlohmann::json & j);
			static Component * Deserialize(const nlohmann::json & j, GameObject *go);
			static component_type typeToComponent;
			static component_type create_map();
		};
	}
}

#endif