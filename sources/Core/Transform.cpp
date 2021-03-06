#include "Core/Transform.hpp"
#include "Core/Json/Json.hpp"

namespace BeerEngine
{
	Transform Transform::basic = Transform();

	Transform::Transform() :
		parent(nullptr), pivot(0.0f), position(0.0f), rotation(), scale(1.0f)
	{}

	Transform::Transform(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale) :
		parent(nullptr), pivot(0.0f), position(position), rotation(rotation), scale(scale)
	{}

	Transform::Transform(const Transform &val)
	{
		*this = val;
	}

	Transform &Transform::operator=(const Transform &val)
	{
		if (this != &val)
		{
			parent = val.parent;
			pivot = val.pivot;
			position = val.position;
			rotation = val.rotation;
			scale = val.scale;
		}
		return (*this);
	}

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

	nlohmann::json	Transform::serialize()
	{
		auto j = JsonSerializable::serialize();
		j.merge_patch({
            {"parent", SERIALIZE_BY_ID(this->parent)},
            {"pivot", this->pivot},
            {"position", this->position},
            {"rotation", this->rotation},
            {"scale", this->scale},
		});
		return j;
	}

	void Transform::deserialize(const nlohmann::json & j, BeerEngine::JsonLoader & loader)
    {
		this->JsonSerializable::deserialize(j, loader);
		DESERIALIZE_BY_ID(this->parent, Transform, "parent", loader);
		this->pivot = j.at("pivot");
		this->position = j.at("position");
		this->rotation = j.at("rotation");
		this->scale = j.at("scale");
    }

	// Not implemented
	Transform * Transform::DeserializePtr(const nlohmann::json & j, BeerEngine::JsonLoader & loader)
	{
		(void) j;
		(void) loader;
		return NULL;
	}

	Transform Transform::Deserialize(const nlohmann::json & j, BeerEngine::JsonLoader & loader)
	{
		Transform t;
		t.deserialize(j, loader);
		return t;
	}
}