#ifndef BE_CORE_HPP
# define BE_CORE_HPP 1
/*!
 * \file Core.hpp
 * \brief Class d'include pour tout les fichier important au projet, libs...
 * \author mgallo, qhonore, jblondea, stmartin, mploux
 */
#define BE_DEBUG 1

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
// GLM
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
// ASSIMP : Model loader
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <cstdlib>
#include <iostream>
#include <ctime>
#include <cmath>
#include <string>
#include <cstring>
#include <sstream>
#include <map>
#include <vector>
#include <stack>
#include <fstream>
#include <functional>
#include <thread>
#include <mutex>

#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720

#include <nuklear.h>
#include "demo/glfw_opengl3/nuklear_glfw_gl3.h"

#include <nlohmann/json.hpp>

#include <signal.h>
/*! \namespace BeerEngine
 * \brief espace de nommage regroupant les fonctionnalité du moteur
 */
namespace BeerEngine
{
    class AScene;
    class GameObject;
    class Transform;
    class JsonSerializable;
	struct Camera;
	/*! \namespace BeerEngine::Audio
	* \brief espace de nommage regroupant les fonctionnalité audio du moteur
	*/
	namespace Audio
	{
		class AudioClip;
		class AudioListener;
		class AudioSource;
	}
	/*! \namespace BeerEngine::Component
	* \brief espace de nommage regroupant les fonctionnalité des BeerEngine::Component du moteur
	*/
	namespace Component
	{
		enum RBType {None, Kinematic, Static};

		class Component;
		class MeshRenderer;
		class RaysRenderer;
        class ACollider;
        class CircleCollider;
        class BoxCollider2D;
		class RigidBody2D;
		class ParticleBase;
		class ParticleExplode;
	}
	/*! \namespace BeerEngine::Graphics
	* \brief espace de nommage regroupant les fonctionnalité graphique du moteur
	*/
    namespace Graphics
	{
		class Graphics;
		class ShaderProgram;
		class Mesh;
		class AMaterial;
		class ALight;
		class Texture;
		class MeshBuilder;
	}
	/*! \namespace BeerEngine::Physics
	* \brief espace de nommage regroupant les fonctionnalité des Physique du moteur
	*/
	namespace Physics
	{
		struct Ray;
		class Physics;
	}
	/*! \namespace BeerEngine::BeerRoutine
	* \brief espace de nommage regroupant les fonctionnalité des routines du moteur
	*/
	namespace BeerRoutine
	{
		class BeerRoutine;
		class ARoutineRunner;
	}
	/*! \namespace BeerEngine::IO
	* \brief espace de nommage regroupant les fonctionnalité des entrées du moteur
	*/
    namespace IO
	{
	}
}

#define REGISTER_COMPONENT_HPP static int RegisterComponentType(); \
							static 	int componentRegisterer;\
							static std::string type;\
							nlohmann::json	serialize();\
        					void deserialize(const nlohmann::json & j, BeerEngine::JsonLoader & loader);

//#define REGISTER_COMPONENT_CPP(Class) int	Class::RegisterComponentType() \
//		{\
//			Component::typeToAddComponent[typeid(Class).name()] = &Component::addComponent<Class>;\
//			return (1);\
//		}\
//		\
//		int Class::componentRegisterer = Class::RegisterComponentType();\
//		std::string Class::type = typeid(Class).name();

#define SERIALIZE_BY_ID(Src) !Src ? nlohmann::json(nullptr) : nlohmann::json(Src->_serializationID)

#define DESERIALIZE_BY_ID(Dest, Class, Key, Loader) \
	Loader.serializationCallBacks.push( \
		[this, j, &loader]() { \
			/* std::cout << "callback of " << #Dest << " on " << Key << std::endl; */\
			/* std::cout << "json is " << j << std::endl; */\
			if (j.find(Key) == j.end()) \
				Dest = NULL; \
			else \
				Dest = dynamic_cast<Class *>(Loader.getSerializableByID(j.at(Key))); \
		} \
	)

 /* For some reason on linux those two preprcessor cause a segfault */
 # ifdef __APPLE__
 #  define REGISTER_COMPONENT_CPP(Class) int	Class::RegisterComponentType() \
		{\
			Component::typeToAddComponent[typeid(Class).name()] = &Component::addComponent<Class>;\
			return (1);\
		}\
		\
		int Class::componentRegisterer = Class::RegisterComponentType();\
		std::string Class::type = typeid(Class).name();
 # else
 #  define REGISTER_COMPONENT_CPP(Class) int	Class::RegisterComponentType() \
		{\
			return (1);\
		}\
		\
		int Class::componentRegisterer = Class::RegisterComponentType();\
		std::string Class::type = typeid(Class).name();
 # endif
#endif
