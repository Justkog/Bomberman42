#ifndef BE_CORE_TRANSFORM_HPP
#define BE_CORE_TRANSFORM_HPP 1

#include "Core.hpp"

namespace BeerEngine
{
    class Transform
	{
	public:
		Transform	*parent;
		glm::vec3	pivot;
		glm::vec3	position;
		glm::quat	rotation;
		glm::vec3	scale;

		Transform();

		void		translate(glm::vec3 pos);
		void		translate(float x, float y, float z);

		glm::vec3	forward(void);
		glm::vec3	left(void);
		glm::vec3	right(void);
		glm::vec3	top(void);

		glm::vec3	getWorldPosition();
		glm::vec3	getWorldRotate(glm::vec3 v);

		glm::mat4	getMat4(bool isCamera = false);

	};
}

#endif