#ifndef BE_CORE_COMPONENT_HPP
#define BE_CORE_COMPONENT_HPP 1

namespace BeerEngine
{
	class GameObject;
	
	namespace Component
	{
		class Component
		{
		protected:
		public:
			Component(GameObject *gameObject);
			virtual ~Component(void) {}

			GameObject		*_gameObject;
		};
	}
}

#endif