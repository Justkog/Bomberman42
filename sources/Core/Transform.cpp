#include "Core/Transform.hpp"

namespace BeerEngine
{
	Transform::Transform() :
		position(0.0f), rotation(), scale(1.0f)
	{}

	glm::mat4	Transform::getMat4(void)
	{
		glm::mat4 mat = glm::translate(glm::vec3(position[0], position[1], -position[2]));
		mat = mat * glm::toMat4(rotation) * glm::translate(glm::vec3(-pivot[0], -pivot[1], pivot[2]));
		mat = glm::scale(mat, scale);
		return (mat);
	}
}