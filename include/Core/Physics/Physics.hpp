#ifndef BE_CORE_PHYSICS_HPP
#define BE_CORE_PHYSICS_HPP 1

#include "Core/Core.hpp"

namespace BeerEngine
{
	namespace Physics
	{
		struct Ray
		{
			glm::vec3 origin;
			glm::vec3 direction;
		};

		class Physics
		{

		public:

			static Ray MouseToWorldRay();
			static Ray ScreenToWorldRay(glm::vec2 screenPosition);
			static bool Raycast(glm::vec3 origin, glm::vec3 direction);
		};
	}
}

#endif