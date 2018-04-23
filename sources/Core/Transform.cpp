#include "Core/Transform.hpp"

namespace BeerEngine
{
	Transform::Transform() :
		parent(nullptr), pivot(0.0f), position(0.0f), rotation(), scale(1.0f)
	{}

	void		Transform::translate(glm::vec3 pos)
	{
		position += pos;
	}

	void		Transform::translate(float x, float y, float z)
	{
		translate(glm::vec3(x, y, z));
	}

	glm::vec3	Transform::forward(void)
	{
		glm::vec4 forward(0.0f, 0.0f, 1.0f, 0.0f);
		forward = rotation * forward;
		return (glm::vec3(forward));
	}

	glm::vec3	Transform::right(void)
	{
		glm::vec4 r(1.0f, 0.0f, 0.0f, 0.0f);
		r = glm::toMat4(rotation) * r;
		r[1] = 0.0f;
		return (glm::normalize(glm::vec3(r)));
	}

	glm::vec3	Transform::top(void)
	{
		return (glm::vec3(0, 1, 0));
	}

	glm::mat4	Transform::getMat4(bool isCamera)
	{
		glm::mat4 mat;
		if (isCamera)
		{
			mat = glm::translate(glm::vec3(position[0], position[1], position[2]));
			mat = glm::toMat4(rotation) * mat;
		}
		else
		{
			mat = glm::translate(glm::vec3(position[0], position[1], -position[2]));
			mat = mat * glm::toMat4(rotation) * glm::translate(glm::vec3(-pivot[0], -pivot[1], pivot[2]));
			mat = glm::scale(mat, scale);
		}
		if (parent != nullptr)
			mat = parent->getMat4() * mat;
		return (mat);
	}
}