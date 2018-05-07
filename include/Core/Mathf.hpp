#ifndef BE_CORE_MATHF_HPP
#define BE_CORE_MATHF_HPP 1

#include "Core.hpp"

namespace BeerEngine
{
	class Mathf
	{
	public:
		static float Range(float min, float max);
		static glm::mat4		assimp_to_glm(aiMatrix4x4 mat);
		static aiMatrix4x4		glm_to_assimp(glm::mat4 mat);
	};
}

#endif