#include "Core/Mathf.hpp"

namespace BeerEngine
{
	float Mathf::Range(float min, float max)
	{
		return (((max - min) * ((float)rand() / RAND_MAX)) + min);
	}
	
	glm::mat4		Mathf::assimp_to_glm(aiMatrix4x4 mat)
	{
		glm::mat4 result;

		result[0][0] = mat.a1;
		result[0][1] = mat.b1;
		result[0][2] = mat.c1;
		result[0][3] = mat.d1;
		result[1][0] = mat.a2;
		result[1][1] = mat.b2;
		result[1][2] = mat.c2;
		result[1][3] = mat.d2;
		result[2][0] = mat.a3;
		result[2][1] = mat.b3;
		result[2][2] = mat.c3;
		result[2][3] = mat.d3;
		result[3][0] = mat.a4;
		result[3][1] = mat.b4;
		result[3][2] = mat.c4;
		result[3][3] = mat.d4;

		return result;
	}

	aiMatrix4x4		Mathf::glm_to_assimp(glm::mat4 mat)
	{
		return aiMatrix4x4(mat[0][0],mat[0][1],mat[0][2],mat[0][3],
						   mat[1][0],mat[1][1],mat[1][2],mat[1][3],
						   mat[2][0],mat[2][1],mat[2][2],mat[2][3],
						   mat[3][0],mat[3][1],mat[3][2],mat[3][3]);
	}
}