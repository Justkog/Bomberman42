#ifndef BE_CORE_COMPONENT_MODELRENDERER_HPP
#define BE_CORE_COMPONENT_MODELRENDERER_HPP 1
/*!
 * \file ModelRenderer.hpp
 * \brief Compoment de rendu d'une animation 3D
 * \author mploux
 */
#include "Core/Core.hpp"
#include "Component.hpp"
#include "IRenderForward.hpp"
#include "IUpdate.hpp"
#include "IRenderShadow.hpp"
#include "Core/Graphics/Lights/ALight.hpp"
#include "Core/Graphics/MeshBuilder.hpp"
#include "Core/Mathf.hpp"
#include "Core/Time.hpp"

namespace BeerEngine
{
	namespace Component
	{
		/*! \class ModelRenderer
		* \brief Classe component pour effectuer la mise a jour et le rendu d'une animation 3D
		*/
		class ModelRenderer : public Component, public IRenderForward, public IUpdate, public IRenderShadow
		{
		protected:
			#define NUM_BONES_PER_VEREX 4

			/*! \struct BoneInfo
			* \brief Structure de stockage des informations d'un bones
			*/
			struct BoneInfo
			{
				aiMatrix4x4 boneOffset;
				glm::mat4 finalTransformation;
			};
			/*! \struct VertexBoneData
			* \brief Structure de stockage des bones par vertex avec leur poids
			*/
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
			
			/*! \struct Animation
			* \brief Structure de stockage des informations d'animation
			*/
			struct Animation
			{
				int index;
				float speed;
			};

			Assimp::Importer 					_importer;
			const aiScene						*_assimpScene;
			std::map<int, Graphics::AMaterial*>	_materials;
			std::map<Graphics::Mesh*, int>		_materialIndices;
			glm::mat4							_mat;
			std::map<std::string, Animation>	_animations;
			Animation							_currentAnimation;
			bool 								_playAnimation;
			bool 								_loopAnimation;
			float 								_animationTime;
			float								_animationSpeed;

			const aiScene		*_scene;

			int					_numMeshes;
			GLsizei				*_drawSize;
			GLuint				*_vao, *_vbo, *_ubo, *_nbo, *_wbo, *_bbo;

			std::map<std:: string, uint>	_boneMapping;
			uint							_numBones;
			std::vector<BoneInfo>			_boneInfo;
			std::vector<glm::mat4> 			_transforms;

			std::vector<float>	_boneTransforms;
			glm::mat4			_globalInverseTransform;

			void build(int id, std::vector<glm::vec3> &positions, std::vector<glm::vec3> &normals, std::vector<glm::vec2> &uvs, std::vector<VertexBoneData> &bones);
			void loadBones(const aiMesh* mesh, std::vector<VertexBoneData>& bones);
			void boneTransform(float timeInSeconds, std::vector<glm::mat4> &transforms);
			const aiNodeAnim *fineNodeAnim(const aiAnimation *anim, const std::string &name);
			void readNodes(float animationTime, const aiNode *node, glm::mat4 &parent);

			void interpolateNodeRotation(aiQuaternion &out, float animationTime, const aiNodeAnim *node);
			void interpolateNodePosition(aiVector3D &out, float animationTime, const aiNodeAnim *node);
			void interpolateNodeScale(aiVector3D &out, float animationTime, const aiNodeAnim *node);

			ModelRenderer();
			ModelRenderer(const ModelRenderer &val);
			ModelRenderer &operator=(const ModelRenderer &val);

		public:
			virtual ~ModelRenderer();

			ModelRenderer(GameObject *gameObject);

			ModelRenderer	&load(const std::string &file);
			ModelRenderer	&addMaterial(const int &index, Graphics::AMaterial *material);
			Graphics::AMaterial	*getMaterial(const int &index);
			const aiScene	*getScene() const { return _scene; };

			void setAnimation(const std::string &animation);
			void setAnimation(int id);
			void setLoopAnimation(bool loop);
			void playAnimation();
			void stopAnimation();
			void resetAnimation();
			double getAnimationDuration();
			void setAnimationTime(double time);
			void setAnimationSpeed(std::string name, float speed);

			virtual void	fixedUpdate(void);
       		virtual void	update(void);
			virtual void	renderUpdate();
			virtual void	render(Graphics::ALight &light);
			virtual void    renderShadowUpdate(void);
			virtual void    renderShadow(void);
			virtual bool	castShadows(void);
			virtual bool	receiveShadows(void);

			GLenum renderMode;

			// nlohmann::json	serialize();
			// virtual void deserialize(const nlohmann::json &j);

			REGISTER_COMPONENT_HPP
		};
	}
}

#endif