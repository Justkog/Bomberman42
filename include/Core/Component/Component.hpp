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
			GameObject		*_gameObject;
		public:
			Component(GameObject *gameObject);
			virtual ~Component(void) {}

		};
	}
}

#endif