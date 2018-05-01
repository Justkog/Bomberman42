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
		glm::vec4 forward(0.0f, 0.0f, -1.0f, 0.0f);
		forward = forward * glm::toMat4(rotation);
		return (glm::vec3(forward));
	}

	glm::vec3	Transform::left(void)
	{
		glm::vec4 r(-1.0f, 0.0f, 0.0f, 0.0f);
		r = r * glm::toMat4(rotation);
		return (glm::vec3(r));
	}

	glm::vec3	Transform::right(void)
	{
		glm::vec4 r(1.0f, 0.0f, 0.0f, 0.0f);
		r = r * glm::toMat4(rotation);
		return (glm::vec3(r));
	}

	glm::vec3	Transform::top(void)
	{
		glm::vec4 r(0.0f, 1.0f, 0.0f, 0.0f);
		r = r * glm::toMat4(rotation);
		return (glm::vec3(r));
	}

	glm::vec3	Transform::getWorldPosition()
	{
		glm::mat4 mat = getMat4();
		float *f = glm::value_ptr(mat);
		return (glm::vec3(f[12], f[13], f[14]));
	}

	glm::vec3	Transform::getWorldRotate(glm::vec3 v)
	{
		glm::vec4 r(v, 0.0f);
		r = r * glm::toMat4(rotation);
		return (glm::vec3(r));
	}

	glm::mat4	Transform::getMat4(bool isCamera)
	{
		glm::mat4 mat;
		if (isCamera)
		{
			mat = glm::translate(glm::vec3(-position[0], -position[1], -position[2]));
			mat = glm::toMat4(rotation) * mat;
		}
		else
		{
			mat = glm::translate(glm::vec3(position[0], position[1], position[2]));
			mat = mat * glm::toMat4(rotation) * glm::translate(glm::vec3(pivot[0], pivot[1], pivot[2]));
			mat = glm::scale(mat, scale);
		}
		if (parent != nullptr)
			mat = parent->getMat4() * mat;
		return (mat);
	}
}