#ifndef BE_CORE_COMPONENT_MODELRENDERER2_HPP
#define BE_CORE_COMPONENT_MODELRENDERER2_HPP 1

#include "Core/Core.hpp"
#include "Component.hpp"
#include "IRender.hpp"
#include "Core/Graphics/MeshBuilder.hpp"
#include "Core/Mathf.hpp"
#include "Core/Time.hpp"

// #include <maths/Vec3.hpp>
// #include <maths/Vec2.hpp>
// #include <vector>
// #include <maths/Mat4.hpp>
// #include "Shader.hpp"
// #include "ModelSkeleton.hpp"
// #include "ModelAnimation.hpp"

namespace BeerEngine
{
	namespace Component
	{
		class Model : public Component, public IRender
		{
		protected:
			#define NUM_BONES_PER_VEREX 4

			struct BoneInfo
			{
				aiMatrix4x4 boneOffset;
				glm::mat4 finalTransformation;
			};

			struct VertexBoneData
			{
				uint ids[NUM_BONES_PER_VEREX];
				float weights[NUM_BONES_PER_VEREX];

				void init()
				{
					bzero(ids, NUM_BONES_PER_VEREX);
					bzero(weights, NUM_BONES_PER_VEREX);
				};

				void addBoneData(uint boneID, float weight)
				{
					for (uint i = 0 ; i < NUM_BONES_PER_VEREX ; i++)
					{
						if (weights[i] == 0.0)
						{
							ids[i] = boneID;
							weights[i] = weight;
							return;
						}
					}
				}
			};

			Assimp::Importer 					_importer;
			const aiScene						*_assimpScene;
			std::map<int, Graphics::AMaterial*>	_materials;
			std::map<Graphics::Mesh*, int>		_materialIndices;
			glm::mat4							_mat;
			int									_currentAnimation;

			const aiScene		*m_scene;

			int					m_numMeshes;
			GLsizei				*m_drawSize;
			GLuint				*m_vao, *m_vbo, *m_ubo, *m_nbo, *m_wbo, *m_bbo;

			// ModelSkeleton		*m_skeleton;
			// ModelAnimation		*m_animations;

			std::map<std:: string, uint>	m_boneMapping;
			uint							m_numBones;
			std::vector<BoneInfo>			m_boneInfo;
			std::vector<glm::mat4> 			m_transforms;

			std::vector<float>	m_boneTransforms;
			glm::mat4			m_globalInverseTransform;

			void build(int id, std::vector<glm::vec3> &positions, std::vector<glm::vec3> &normals, std::vector<glm::vec2> &uvs, std::vector<VertexBoneData> &bones);
			void loadBones(uint meshIndex, const aiMesh* mesh, std::vector<VertexBoneData>& bones);
			void boneTransform(float timeInSeconds, std::vector<glm::mat4> &transforms);
			const aiNodeAnim *fineNodeAnim(const aiAnimation *anim, const std::string &name);
			void readNodes(float animationTime, const aiNode *node, glm::mat4 &parent);

			void interpolateNodeRotation(aiQuaternion &out, float animationTime, const aiNodeAnim *node);
			void interpolateNodePosition(aiVector3D &out, float animationTime, const aiNodeAnim *node);
			void interpolateNodeScale(aiVector3D &out, float animationTime, const aiNodeAnim *node);

		public:
			Model(GameObject *gameObject);
			~Model();

			Model	&load(const std::string &file);
			Model	&addMaterial(const int &index, Graphics::AMaterial *material);
			Graphics::AMaterial	*getMaterial(const int &index);

			virtual void renderUpdate();
			virtual void render();

			GLenum renderMode;

			nlohmann::json	serialize();
			virtual void deserialize(const nlohmann::json & j);

			REGISTER_COMPONENT_HPP

			// ModelSkeleton	*getSkeleton() const { return m_skeleton; };
			// ModelAnimation	*getAnimations() const { return m_animations; };
			const aiScene	*getScene() const { return m_scene; };
		};

	}
}

#endif