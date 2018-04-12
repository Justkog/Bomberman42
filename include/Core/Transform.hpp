#ifndef BE_CORE_TRANSFORM_HPP
#define BE_CORE_TRANSFORM_HPP 1

#include "Core.hpp"

namespace BeerEngine
{
    class Transform
	{
	public:
		glm::vec3	pivot;
		glm::vec3	position;
		glm::quat	rotation;
		glm::vec3	scale;

		Transform();

		glm::mat4	getMat4(void);

	};
}

#endif