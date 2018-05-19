//
// Created by mploux on 04/05/18.
//

#include <iostream>
#include <Core/SceneManager.hpp>
// #include <Core.hpp>
// #include <maths/glmUtils.hpp>
#include "Core/Component/ModelRenderer.hpp"
#include "Core/Graphics/Graphics.hpp"
#include "Core/GameObject.hpp"
#include "Core/Graphics/AMaterial.hpp"
#include "Core/Json/Json.hpp"
#include "Core/Mathf.hpp"
#include "Core/Graphics/Lights/ALight.hpp"

namespace BeerEngine
{
	namespace Component
	{
		ModelRenderer::ModelRenderer(GameObject *gameObject) :
			Component(gameObject),
			renderMode(GL_TRIANGLES),
			_assimpScene(nullptr),
			_animationTime(0),
			_playAnimation(false),
			_animationSpeed(1)
		{}

		ModelRenderer::ModelRenderer()
		{}

		ModelRenderer::ModelRenderer(const ModelRenderer &val)
		{
			*this = val;
		}
		
		ModelRenderer &ModelRenderer::operator=(const ModelRenderer &val)
		{
			if (this != &val)
			{
				ModelRenderer::~ModelRenderer();

				_importer = val._importer;
				_assimpScene = val._assimpScene;
				for (const std::pair<int, Graphics::AMaterial*> &p : val._materials)
					_materials[p.first] = p.second;
				for (const std::pair<Graphics::Mesh*, int> &p : val._materialIndices)
					_materialIndices[p.first] = p.second;
				_mat = val._mat;
				for (const std::pair<std::string, Animation> &p : val._animations)
					_animations[p.first] = p.second;
				
				_currentAnimation = val._currentAnimation;
				_playAnimation = val._playAnimation;
				_loopAnimation = val._loopAnimation;
				_animationTime = val._animationTime;
				_animationSpeed = val._animationSpeed;
				_scene = val._scene;
				_numMeshes = val._numMeshes;
				_drawSize = val._drawSize;
				
				_vao = val._vao; 
				_vbo = val._vbo; 
				_ubo = val._ubo; 
				_nbo = val._nbo; 
				_wbo = val._wbo; 
				_bbo = val._bbo;

				for (const std::pair<std:: string, uint> &p : val._boneMapping)
					_boneMapping[p.first] = p.second;
				_numBones = val._numBones;
				for (int i = 0; i < val._boneInfo.size(); i++)
					_boneInfo.push_back(val._boneInfo[i]);
				for (int i = 0; i < val._transforms.size(); i++)
					_transforms.push_back(val._transforms[i]);
				for (int i = 0; i < val._boneTransforms.size(); i++)
					_boneTransforms.push_back(val._boneTransforms[i]);
				_globalInverseTransform = val._globalInverseTransform;
			}
			return (*this);
		}

		ModelRenderer	&ModelRenderer::load(const std::string &file)
		{
			_scene = _importer.ReadFile(file.c_str(), aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs | aiProcess_JoinIdenticalVertices | aiProcess_LimitBoneWeights);

			if (!_scene)
			{
				std::cerr << "Invalid ModelRenderer file !" << std::endl;
				exit(EXIT_FAILURE);
			}

			for (int i = 0; i < _scene->mNumAnimations; i++)
			{
				_animations[_scene->mAnimations[i]->mName.data].index = i;
				_animations[_scene->mAnimations[i]->mName.data].speed = 1;
				std::cout << "Animation: " << _scene->mAnimations[i]->mName.data << std::endl;
			}

			aiMatrix4x4 globalInverseTransform = _scene->mRootNode->mTransformation;
			globalInverseTransform = globalInverseTransform.Inverse();
			_globalInverseTransform = Mathf::assimp_to_glm(globalInverseTransform);

			_numMeshes = _scene->mNumMeshes;
			_vao = new GLuint[_scene->mNumMeshes];
			_vbo = new GLuint[_scene->mNumMeshes];
			_ubo = new GLuint[_scene->mNumMeshes];
			_nbo = new GLuint[_scene->mNumMeshes];
			_bbo = new GLuint[_scene->mNumMeshes];
			_wbo = new GLuint[_scene->mNumMeshes];
			_drawSize = new int[_scene->mNumMeshes];
			_currentAnimation.index = 0;

			_numBones = 0;

			for (std::size_t k = 0; k < _scene->mNumMeshes; k++)
			{
				aiMesh *mesh = _scene->mMeshes[k];

				std::vector<glm::vec3>	positions;
				std::vector<glm::vec3>	normals;
				std::vector<glm::vec2>	texcoords;
				std::vector<VertexBoneData>	bones;

				positions.reserve(mesh->mNumVertices);
				normals.reserve(mesh->mNumVertices);
				texcoords.reserve(mesh->mNumVertices);
				bones.resize(mesh->mNumVertices);

				if (_scene->HasAnimations())
					loadBones(k, mesh, bones);

				for (std::size_t i = 0; i < mesh->mNumVertices; i++)
				{
					positions.push_back(glm::vec3(mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z));
					normals.push_back(glm::vec3(mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z));
					if(mesh->HasTextureCoords(0))
						texcoords.push_back(glm::vec2(mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y));
				}

				std::vector<glm::vec3>	indexedPpositions;
				std::vector<glm::vec3>	indexedNormals;
				std::vector<glm::vec2>	indexedTexcoords;
				std::vector<VertexBoneData>	indexedBonesData;

				for (std::size_t i = 0; i < mesh->mNumFaces; i++)
				{
					aiFace face = mesh->mFaces[i];
					for (std::size_t j = 0; j < face.mNumIndices; j++)
					{
						int index = face.mIndices[j];

						glm::vec3 position = positions[index];
						indexedPpositions.push_back(position);

						glm::vec3 normal = normals[index];
						indexedNormals.push_back(normal);

						if(mesh->HasTextureCoords(0))
						{
							glm::vec2 texcoord = texcoords[index];
							indexedTexcoords.push_back(texcoord);
						}
						indexedBonesData.push_back(bones[index]);
					}
				}
				build(k, indexedPpositions, indexedNormals, indexedTexcoords, indexedBonesData);
			}
			if (_scene->HasAnimations())
				boneTransform(0, _transforms);
			return *this;
		}

		ModelRenderer::~ModelRenderer()
		{
			if (_drawSize != nullptr)
				delete _drawSize;
			if (_vao != nullptr)
				glDeleteVertexArrays(_numMeshes, _vao);
			if (_vbo != nullptr)
				glDeleteBuffers(_numMeshes, _vbo);
			if (_ubo != nullptr)
				glDeleteBuffers(_numMeshes, _ubo);
			if (_nbo != nullptr)
				glDeleteBuffers(_numMeshes, _nbo);
			if (_wbo != nullptr)
				glDeleteBuffers(_numMeshes, _wbo);
			if (_bbo != nullptr)
				glDeleteBuffers(_numMeshes, _bbo);
		}

		void ModelRenderer::loadBones(uint meshIndex, const aiMesh* mesh, std::vector<VertexBoneData>& bones)
		{
			for (uint i = 0 ; i < mesh->mNumBones ; i++)
			{
				uint boneIndex = 0;
				std::string boneName(mesh->mBones[i]->mName.data);
				if (_boneMapping.find(boneName) == _boneMapping.end())
				{
					boneIndex = _numBones;
					_numBones++;
					BoneInfo bi;
					_boneInfo.push_back(bi);
				}
				else
					boneIndex = _boneMapping[boneName];
				_boneMapping[boneName] = boneIndex;
				_boneInfo[boneIndex].boneOffset = mesh->mBones[i]->mOffsetMatrix;
				for (uint j = 0 ; j < mesh->mBones[i]->mNumWeights ; j++)
				{
					uint vertexID = mesh->mBones[i]->mWeights[j].mVertexId;
					float weight = mesh->mBones[i]->mWeights[j].mWeight;
					bones[vertexID].addBoneData(boneIndex, weight);
				}
			}
		}

		void ModelRenderer::boneTransform(float timeInSeconds, std::vector<glm::mat4 > &transforms)
		{
			glm::mat4 identity;

			float ticksPerSecond = _scene->mAnimations[_currentAnimation.index]->mTicksPerSecond != 0 ? _scene->mAnimations[_currentAnimation.index]->mTicksPerSecond : 25.0f;
			float timeInTicks = timeInSeconds;
			float animationTime = timeInTicks >= _scene->mAnimations[_currentAnimation.index]->mDuration ? _scene->mAnimations[_currentAnimation.index]->mDuration - 1 : timeInTicks;
			if (_loopAnimation)
				animationTime = fmod(timeInTicks, _scene->mAnimations[_currentAnimation.index]->mDuration);
			readNodes(animationTime, _scene->mRootNode, identity);
			transforms.resize(_numBones);
			for (uint i = 0 ; i < _numBones ; i++)
				transforms[i] = _boneInfo[i].finalTransformation;
		}

		const aiNodeAnim *ModelRenderer::fineNodeAnim(const aiAnimation *anim, const std::string &name)
		{
			for (uint i = 0 ; i < anim->mNumChannels ; i++)
			{
				const aiNodeAnim* pNodeAnim = anim->mChannels[i];
				if (std::string(pNodeAnim->mNodeName.data) == name)
					return pNodeAnim;
			}
			return nullptr;
		}

		void ModelRenderer::readNodes(float animationTime, const aiNode *node, glm::mat4 &parent)
		{
			std::string nodeName(node->mName.data);

			const aiAnimation *anim = _scene->mAnimations[_currentAnimation.index];
			const aiNodeAnim *animNode = fineNodeAnim(anim, node->mName.data);
			glm::mat4 boneTransform = Mathf::assimp_to_glm(node->mTransformation);
			if (animNode)
			{
				aiVector3D Scaling;
				interpolateNodeScale(Scaling, animationTime, animNode);
				glm::mat4 scaling = glm::scale(glm::mat4(1.0f), glm::vec3(Scaling.x, Scaling.y, Scaling.z));
				aiQuaternion RotationQ;
				interpolateNodeRotation(RotationQ, animationTime, animNode);
				glm::mat4 rotation = Mathf::assimp_to_glm(aiMatrix4x4t<float>(RotationQ.GetMatrix()));
				aiVector3D Translation;
				interpolateNodePosition(Translation, animationTime, animNode);
				glm::mat4 translation = glm::translate(glm::mat4(1.0f), glm::vec3(Translation.x, Translation.y, Translation.z));
				boneTransform = translation * rotation * scaling;
			}
			glm::mat4 aiFinalBoneTransformation = parent * boneTransform;
			if (_boneMapping.find(nodeName) != _boneMapping.end())
			{
				uint BoneIndex = _boneMapping[nodeName];
				glm::mat4 trs = _globalInverseTransform * aiFinalBoneTransformation * Mathf::assimp_to_glm(_boneInfo[BoneIndex].boneOffset);
				_boneInfo[BoneIndex].finalTransformation = trs;
			}
			for (std::size_t i = 0; i < node->mNumChildren; i++)
				readNodes(animationTime, node->mChildren[i], aiFinalBoneTransformation);
		}

		void ModelRenderer::build(int i, std::vector<glm::vec3> &positions, std::vector<glm::vec3> &normals, std::vector<glm::vec2> &uvs, std::vector<VertexBoneData> &bones)
		{
			if (positions.size() != normals.size())
				throw std::runtime_error("Invalid ModelRenderer !");

			GLfloat *vBuffer = new GLfloat[positions.size() * 3];
			GLfloat *uBuffer = new GLfloat[uvs.size() * 2];
			GLfloat *nBuffer = new GLfloat[normals.size() * 3];
			GLuint *bBuffer = new GLuint[positions.size() * 4];
			GLfloat *wBuffer = new GLfloat[positions.size() * 4];

			for (std::size_t i = 0; i < positions.size(); i++)
			{
				vBuffer[i * 3 + 0] = positions[i].x;
				vBuffer[i * 3 + 1] = positions[i].y;
				vBuffer[i * 3 + 2] = positions[i].z;
			}
			for (std::size_t i = 0; i < uvs.size(); i++)
			{
				uBuffer[i * 2 + 0] = uvs[i].x;
				uBuffer[i * 2 + 1] = uvs[i].y;
			}
			for (std::size_t i = 0; i < normals.size(); i++)
			{
				nBuffer[i * 3 + 0] = normals[i].x;
				nBuffer[i * 3 + 1] = normals[i].y;
				nBuffer[i * 3 + 2] = normals[i].z;
			}
			for (std::size_t i = 0; i < positions.size(); i++)
			{
				wBuffer[i * 4 + 0] = bones[i].weights[0];
				wBuffer[i * 4 + 1] = bones[i].weights[1];
				wBuffer[i * 4 + 2] = bones[i].weights[2];
				wBuffer[i * 4 + 3] = bones[i].weights[3];

				bBuffer[i * 4 + 0] = bones[i].ids[0];
				bBuffer[i * 4 + 1] = bones[i].ids[1];
				bBuffer[i * 4 + 2] = bones[i].ids[2];
				bBuffer[i * 4 + 3] = bones[i].ids[3];
			}

			_drawSize[i] = static_cast<GLsizei>(positions.size());

			glGenVertexArrays(1, &_vao[i]);
			glGenBuffers(1, &_vbo[i]);
			glGenBuffers(1, &_ubo[i]);
			glGenBuffers(1, &_nbo[i]);
			glGenBuffers(1, &_bbo[i]);
			glGenBuffers(1, &_wbo[i]);

			glBindVertexArray(_vao[i]);

			glEnableVertexAttribArray(0);
			glBindBuffer(GL_ARRAY_BUFFER, _vbo[i]);
			glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * positions.size() * 3, vBuffer, GL_STATIC_DRAW);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

			glEnableVertexAttribArray(1);
			glBindBuffer(GL_ARRAY_BUFFER, _nbo[i]);
			glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * normals.size() * 3, nBuffer, GL_STATIC_DRAW);
			glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

			glEnableVertexAttribArray(2);
			glBindBuffer(GL_ARRAY_BUFFER, _ubo[i]);
			glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * uvs.size() * 2, uBuffer, GL_STATIC_DRAW);
			glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, nullptr);

			glEnableVertexAttribArray(5);
			glBindBuffer(GL_ARRAY_BUFFER, _bbo[i]);
			glBufferData(GL_ARRAY_BUFFER, sizeof(GLuint) * positions.size() * 4, bBuffer, GL_STATIC_DRAW);
			glVertexAttribIPointer(5, 4, GL_UNSIGNED_INT, 0, nullptr);

			glEnableVertexAttribArray(6);
			glBindBuffer(GL_ARRAY_BUFFER, _wbo[i]);
			glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * positions.size() * 4, wBuffer, GL_STATIC_DRAW);
			glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, 0, nullptr);

			glBindVertexArray(0);

			delete[] vBuffer;
			delete[] uBuffer;
			delete[] nBuffer;
			delete[] bBuffer;
			delete[] wBuffer;
		}

		void ModelRenderer::setAnimation(const std::string &animation)
		{
			if (_animations.find(animation) == _animations.end())
				return;
			_currentAnimation = _animations[animation];
		}

		void ModelRenderer::setAnimation(int id)
		{
			if (id >= _scene->mNumAnimations)
				return;
			_currentAnimation.index = id;
		}

		void ModelRenderer::setLoopAnimation(bool loop)
		{
			_loopAnimation = loop;
		}

		void ModelRenderer::playAnimation()
		{
			_playAnimation = true;
		}

		void ModelRenderer::stopAnimation()
		{
			_playAnimation = false;
		}

		void ModelRenderer::resetAnimation()
		{
			_animationTime = 0;
		}

		double ModelRenderer::getAnimationDuration()
		{
			if (!_scene->HasAnimations())
				return 0.0;
			return _scene->mAnimations[_currentAnimation.index]->mDuration;
		}

		void ModelRenderer::setAnimationSpeed(std::string name, float speed)
		{
			_animations[name].speed = speed;
		}

		void ModelRenderer::setAnimationTime(double time)
		{
			_animationTime = time;
		}

		void ModelRenderer::fixedUpdate(void)
		{
			if (_scene->HasAnimations())
			{
				static float lastAnimationTime = _animationTime;
				if (_playAnimation)
				{
					_animationTime += 1 * _currentAnimation.speed;
				}
				if (_playAnimation || _animationTime != lastAnimationTime)
				{
					boneTransform(_animationTime, _transforms);
					lastAnimationTime = _animationTime;
				}
			}
		}

       	void ModelRenderer::update(void)
		{
			
		}

		void ModelRenderer::renderUpdate(void)
		{
			_mat = _gameObject->transform.getMat4();
		}

		void ModelRenderer::render(Graphics::ALight &light)
		{
			if (_materials.empty())
				return;

			_materials[0]->bind(_mat, light);
			light.getShader().uniform1i("hasBones", _scene->HasAnimations() ? 1 : 0);

			for (int i = 0; i < _transforms.size(); i++)
			{
				std::string uniform = "bonesTransforms[" + std::to_string(i) + "]";
				light.getShader().uniformMat(uniform, _transforms[i]);
			}
			for (int i = 0; i < _numMeshes; i++)
			{
				glBindVertexArray(_vao[i]);
				glDrawArrays(GL_TRIANGLES, 0, _drawSize[i]);
			}
			glBindVertexArray(0);
		}

		void    ModelRenderer::renderShadowUpdate(void)
		{

		}

		void    ModelRenderer::renderShadow(void)
		{
			Graphics::Graphics::shadowRenderShader->uniformMat("model", _mat);
			Graphics::Graphics::shadowRenderShader->uniform1i("hasBones", _scene->HasAnimations() ? 1 : 0);
			for (int i = 0; i < _transforms.size(); i++)
			{
				std::string uniform = "bonesTransforms[" + std::to_string(i) + "]";
				Graphics::Graphics::shadowRenderShader->uniformMat(uniform, _transforms[i]);
			}
			for (int i = 0; i < _numMeshes; i++)
			{
				glBindVertexArray(_vao[i]);
				glDrawArrays(GL_TRIANGLES, 0, _drawSize[i]);
			}
			glBindVertexArray(0);
		}

		bool	ModelRenderer::castShadows(void)
		{
			return true;
		}

		bool	ModelRenderer::receiveShadows(void)
		{
			return true;
		}


		static uint findRotation(float animationTime, const aiNodeAnim *node)
		{
			for (uint i = 0 ; i < node->mNumRotationKeys - 1 ; i++)
				if (animationTime < (float)node->mRotationKeys[i + 1].mTime)
					return i;
			return 0;
		}

		static uint findPosition(float animationTime, const aiNodeAnim *node)
		{
			for (uint i = 0 ; i < node->mNumPositionKeys - 1 ; i++)
				if (animationTime < (float)node->mPositionKeys[i + 1].mTime)
					return i;
			return 0;
		}

		static uint findScale(float animationTime, const aiNodeAnim *node)
		{
			for (uint i = 0 ; i < node->mNumScalingKeys - 1 ; i++)
				if (animationTime < (float)node->mScalingKeys[i + 1].mTime)
					return i;
			return 0;
		}

		void ModelRenderer::interpolateNodeRotation(aiQuaternion &out, float animationTime, const aiNodeAnim *node)
		{
			if (node->mNumRotationKeys == 1)
			{
				out = node->mRotationKeys[0].mValue;
				return;
			}

			uint index = findRotation(animationTime, node);
			uint nextIndex = (index + 1);
			float delta = node->mRotationKeys[nextIndex].mTime - node->mRotationKeys[index].mTime;
			float factor = (animationTime - (float)node->mRotationKeys[index].mTime) / delta;
			const aiQuaternion& start = node->mRotationKeys[index].mValue;
			const aiQuaternion& end = node->mRotationKeys[nextIndex].mValue;
			aiQuaternion::Interpolate(out, start, end, factor);
			out = out.Normalize();
		}

		void ModelRenderer::interpolateNodePosition(aiVector3D &out, float animationTime, const aiNodeAnim *node)
		{
			if (node->mNumPositionKeys == 1)
			{
				out = node->mPositionKeys[0].mValue;
				return;
			}

			uint index = findPosition(animationTime, node);
			uint nextIndex = (index + 1);
			float delta = node->mPositionKeys[nextIndex].mTime - node->mPositionKeys[index].mTime;
			float factor = (animationTime - (float)node->mPositionKeys[index].mTime) / delta;
			const aiVector3D& start = node->mPositionKeys[index].mValue;
			const aiVector3D& end = node->mPositionKeys[nextIndex].mValue;
			out = start + (end - start) * factor;
		}

		void ModelRenderer::interpolateNodeScale(aiVector3D &out, float animationTime, const aiNodeAnim *node)
		{
			if (node->mNumPositionKeys == 1)
			{
				out = node->mPositionKeys[0].mValue;
				return;
			}

			uint index = findScale(animationTime, node);
			uint nextIndex = (index + 1);
			float delta = node->mScalingKeys[nextIndex].mTime - node->mScalingKeys[index].mTime;
			float factor = (animationTime - (float)node->mScalingKeys[index].mTime) / delta;
			const aiVector3D& start = node->mScalingKeys[index].mValue;
			const aiVector3D& end = node->mScalingKeys[nextIndex].mValue;
			out = start + (end - start) * factor;
		}

		Graphics::AMaterial	*ModelRenderer::getMaterial(const int &index)
		{
			if (_materials.find(index) == _materials.end())
			{
				std::cerr << "Invalid ModelRenderer material index !" << std::endl;
				exit(1);
			}
			return (_materials[index]);
		}

		ModelRenderer	&ModelRenderer::addMaterial(const int &index, Graphics::AMaterial *material)
		{
			std::cout << "Adding: " << material << std::endl;
			_materials[index] = material;
			return (*this);
		}

		nlohmann::json	ModelRenderer::serialize()
		{
			return nlohmann::json {
				{"componentClass", typeid(ModelRenderer).name()},
				// {"mesh", _mesh},
				// {"material", _material},
				{"pivot", _mat},
			};
		}

		void ModelRenderer::deserialize(const nlohmann::json & j, BeerEngine::JsonLoader & loader)
		{
			// std::cout << this->_sourceFile << "\n";
			// this->_sourceFile = j.at("sourceFile");
			// if (this->_sourceFile != "")
			// 	this->setMesh(this->_sourceFile);
			// this->setMesh(Graphics::Mesh::Deserialize(j.at("mesh")));
			// this->setMaterial(Graphics::AMaterial::Deserialize(j.at("material")));
			// this->_mat = j.at("pivot");
		}

		REGISTER_COMPONENT_CPP(ModelRenderer)

	}
}