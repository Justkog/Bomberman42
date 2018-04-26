#include "Core/Transform.hpp"

namespace BeerEngine
{
	Transform::Transform() :
		parent(nullptr),position(0.0f), rotation(), scale(1.0f)
	{}

	void		Transform::translate(Maths::Vector3f pos)
	{
		position += pos;
	}

	void		Transform::translate(float x, float y, float z)
	{
		translate(Maths::Vector3f(x, y, z));
	}

	// glm::vec3	Transform::forward(void)
	// {
	// 	glm::vec4 forward(0.0f, 0.0f, 1.0f, 0.0f);
	// 	forward = forward * glm::toMat4(rotation);
	// 	return (glm::vec3(forward));
	// }

	// glm::vec3	Transform::left(void)
	// {
	// 	glm::vec4 r(1.0f, 0.0f, 0.0f, 0.0f);
	// 	r = r * glm::toMat4(rotation);
	// 	return (glm::vec3(r));
	// }

	// glm::vec3	Transform::right(void)
	// {
	// 	glm::vec4 r(-1.0f, 0.0f, 0.0f, 0.0f);
	// 	r = r * glm::toMat4(rotation);
	// 	return (glm::vec3(r));
	// }

	// glm::vec3	Transform::top(void)
	// {
	// 	glm::vec4 r(0.0f, -1.0f, 0.0f, 0.0f);
	// 	r = r * glm::toMat4(rotation);
	// 	return (glm::vec3(r));
	// }

	Maths::Matrix4x4	Transform::getMat4(bool isCamera)
	{
		Maths::Matrix4x4 mat;
		if (isCamera)
		{
			mat = Maths::Matrix4x4::Translate(position * -1.0f);
			// mat = glm::toMat4(rotation) * mat;
			mat = mat * Maths::Matrix4x4::Euler(rotation);
		}
		else
		{
			mat = Maths::Matrix4x4::Translate(position) * Maths::Matrix4x4::Euler(rotation) * Maths::Matrix4x4::Scale(scale);
			// mat = Maths::Matrix4x4::Euler(rotation) * mat;
			// mat = mat * Maths::Matrix4x4::Translate(pivot);
			// mat = mat * glm::toMat4(rotation) * glm::translate(glm::vec3(pivot[0], pivot[1], pivot[2]));
			// mat = glm::scale(mat, scale);
			// mat = mat * Maths::Matrix4x4::Scale(scale);
		}
		if (parent != nullptr)
			mat = parent->getMat4() * mat;
		return (mat);
	}
}