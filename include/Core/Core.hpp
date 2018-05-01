#ifndef BE_CORE_HPP
# define BE_CORE_HPP 1

#define BE_DEBUG 1

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <glm/vec2.hpp> // glm::vec2
#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include <glm/geometric.hpp>// glm::cross, glm::normalize
#include <glm/gtc/type_ptr.hpp> // glm::value_ptr
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>

#include <cstdlib>
#include <iostream>
#include <ctime>
#include <cmath>
#include <string>
#include <cstring>
#include <sstream>
#include <map>
#include <vector>
#include <fstream>

#include <nuklear.h>
#include <nuklear_glfw_gl3.h>

#include <nlohmann/json.hpp>

#define MAX_VERTEX_BUFFER 512 * 1024
#define MAX_ELEMENT_BUFFER 128 * 1024

namespace BeerEngine
{
    class AScene;
    class GameObject;
    class Transform;
    class JsonSerializable;
	class Camera;

	namespace Audio
	{
		class AudioClip;
		class AudioListener;
		class AudioSource;
	}

	namespace Component
	{
		class Component;
		class MeshRenderer;
        class CircleCollider;
        class BoxCollider2D;
		class RigidBody2D;
	}

    namespace Graphics
	{
		class Graphics;
		class ShaderProgram;
		class Mesh;
		class AMaterial;
		class Texture;
		class MeshBuilder;
		class Particles;
	}
}

#define REGISTER_COMPONENT_HPP static int RegisterComponentType(); \
							static 	int componentRegisterer;

#define REGISTER_COMPONENT_CPP(Class) int	Class::RegisterComponentType() \
		{\
			Component::typeToComponent[typeid(Class).name()] = &Component::createInstance<Class>;\
			return (1);\
		}\
		\
		int Class::componentRegisterer = Class::RegisterComponentType();

#endif