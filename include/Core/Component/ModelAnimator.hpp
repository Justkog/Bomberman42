#ifndef BE_CORE_COMPONENT_MODELANIMATOR_HPP
#define BE_CORE_COMPONENT_MODELANIMATOR_HPP 1

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
		class ModelAnimator : public Component, public IRender
		{
		protected:
			Assimp::Importer 					_importer;
			const aiScene						*_assimpScene;
			int									_currentAnimation;

			const aiScene		*_scene;

			int					_numMeshes;

			std::map<std:: string, uint>	_boneMapping;
			uint							_numBones;
			std::vector<BoneInfo>			_boneInfo;
			std::vector<glm::mat4> 			_transforms;

			std::vector<float>	_boneTransforms;
			glm::mat4			_globalInverseTransform;

			void loadBones(uint meshIndex, const aiMesh* mesh, std::vector<VertexBoneData>& bones);
			void boneTransform(float timeInSeconds, std::vector<glm::mat4> &transforms);
			const aiNodeAnim *fineNodeAnim(const aiAnimation *anim, const std::string &name);
			void readNodes(float animationTime, const aiNode *node, glm::mat4 &parent);

			void interpolateNodeRotation(aiQuaternion &out, float animationTime, const aiNodeAnim *node);
			void interpolateNodePosition(aiVector3D &out, float animationTime, const aiNodeAnim *node);
			void interpolateNodeScale(aiVector3D &out, float animationTime, const aiNodeAnim *node);

		public:
			ModelAnimator(GameObject *gameObject);
			~ModelAnimator();

			void setScene(const aiScene	*scene) { _scene = scene; };
			const aiScene	*getScene() const { return _scene; };

			virtual void renderUpdate();
			virtual void render();

			GLenum renderMode;

			nlohmann::json	serialize();
			virtual void deserialize(const nlohmann::json &j);

			REGISTER_COMPONENT_HPP
		};
	}
}