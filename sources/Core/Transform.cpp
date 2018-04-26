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

	Maths::Vector3f		Transform::forward(void)
	{
		Maths::Vector3f vec;
		float cosY = (float)std::cos(rotation[1] - M_TORADIANS(90));
		float sinY = (float)std::sin(rotation[1] - M_TORADIANS(90));
		float cosP = (float)std::cos(-rotation[0]);
		float sinP = (float)std::sin(-rotation[0]);
		vec.set(cosY * cosP, -sinP, -(sinY * cosP));
		vec.normalize();
		return (vec);
	}

	Maths::Vector3f		Transform::straf(void)
	{
		Maths::Vector3f vec;
		float cosY = (float) std::cos(rotation[1]);
		float sinY = (float) std::sin(rotation[1]);
		float cosP = (float) std::cos(-rotation[0]);
		vec.set(cosY * cosP, 0.0f, -(sinY * cosP));
		vec.normalize();
		return (vec);
	}

	Maths::Matrix4x4	Transform::getMat4(bool isCamera)
	{
		Maths::Matrix4x4 mat;
		mat = Maths::Matrix4x4::RotateX(rotation[0]) * Maths::Matrix4x4::RotateY(rotation[1]) * Maths::Matrix4x4::RotateZ(rotation[2]);
		if (isCamera)
		{
			mat = mat * Maths::Matrix4x4::Translate(position * -1.0f);
		}
		else
		{
			mat = Maths::Matrix4x4::Translate(position) * mat * Maths::Matrix4x4::Scale(scale);
		}
		if (parent != nullptr)
			mat = parent->getMat4() * mat;
		return (mat);
	}
}