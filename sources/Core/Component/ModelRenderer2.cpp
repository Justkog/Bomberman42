//
// Created by mploux on 04/05/18.
//

#include <iostream>
// #include <Core.hpp>
// #include <maths/glmUtils.hpp>
#include "Core/Component/ModelRenderer2.hpp"
#include "Core/Component/ModelRenderer.hpp"
#include "Core/Graphics/Graphics.hpp"
#include "Core/GameObject.hpp"
#include "Core/Graphics/AMaterial.hpp"
#include "Core/Json/Json.hpp"
#include "Core/Mathf.hpp"

namespace BeerEngine
{
	namespace Component
	{
		Model::Model(GameObject *gameObject) :
			Component(gameObject),
			renderMode(GL_TRIANGLES),
			_assimpScene(nullptr)
		{}

		Model	&Model::load(const std::string &file)
		{
			Assimp::Importer importer;
			m_scene = importer.ReadFile(file.c_str(), aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs | aiProcess_JoinIdenticalVertices);

			if (!m_scene)
			{
				std::cerr << "Invalid model file !" << std::endl;
				exit(EXIT_FAILURE);
			}

			for (int i = 0; i < m_scene->mNumAnimations; i++)
			{
				std::cout << "Animation: " << m_scene->mAnimations[i]->mName.data << std::endl;
			}

		//	m_animations = new ModelAnimation(*this);
		//	m_animations->loadAnimation();

			// m_skeleton = new ModelSkeleton(*this);
		//	Mat4<float> identity = Mat4<float>().identity();
		//	readNodes(0, m_scene->mRootNode, identity);

			aiMatrix4x4 globalInverseTransform = m_scene->mRootNode->mTransformation;
			globalInverseTransform.Inverse();
			m_globalInverseTransform = globalInverseTransform;

			m_numMeshes = m_scene->mNumMeshes;
			m_vao = new GLuint[m_scene->mNumMeshes];
			m_vbo = new GLuint[m_scene->mNumMeshes];
			m_ubo = new GLuint[m_scene->mNumMeshes];
			m_nbo = new GLuint[m_scene->mNumMeshes];
			m_bbo = new GLuint[m_scene->mNumMeshes];
			m_wbo = new GLuint[m_scene->mNumMeshes];
			m_drawSize = new int[m_scene->mNumMeshes];

			m_numBones = 0;

			for (std::size_t k = 0; k < m_scene->mNumMeshes; k++)
			{
				aiMesh *mesh = m_scene->mMeshes[k];

				std::vector<glm::vec3>	positions;
				std::vector<glm::vec3>	normals;
				std::vector<glm::vec2>	texcoords;
				std::vector<VertexBoneData>	bones;

				positions.reserve(mesh->mNumVertices);
				normals.reserve(mesh->mNumVertices);
				texcoords.reserve(mesh->mNumVertices);
				bones.resize(mesh->mNumVertices);

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

			// boneTransform(0, m_transforms);
			// m_skeleton->buildMesh();
			return *this;
		}

		Model::~Model()
		{
			// delete m_skeleton;

			delete[] m_vao;
			delete[] m_vbo;
			delete[] m_ubo;
			delete[] m_nbo;
			delete[] m_bbo;
			delete[] m_wbo;
		}

		void Model::loadBones(uint meshIndex, const aiMesh* mesh, std::vector<VertexBoneData>& bones)
		{
			for (uint i = 0 ; i < mesh->mNumBones ; i++)
			{
				uint boneIndex = 0;
				std::string boneName(mesh->mBones[i]->mName.data);

				if (m_boneMapping.find(boneName) == m_boneMapping.end())
				{
					boneIndex = m_numBones;
					m_numBones++;
					BoneInfo bi;
					m_boneInfo.push_back(bi);
				}
				else
				{
					boneIndex = m_boneMapping[boneName];
				}

				m_boneMapping[boneName] = boneIndex;
				m_boneInfo[boneIndex].boneOffset = mesh->mBones[i]->mOffsetMatrix;

				for (uint j = 0 ; j < mesh->mBones[i]->mNumWeights ; j++)
				{
					uint vertexID = mesh->mBones[i]->mWeights[j].mVertexId;
					float weight = mesh->mBones[i]->mWeights[j].mWeight;
					bones[vertexID].addBoneData(boneIndex, weight);
				}
			}
		}

		void Model::boneTransform(float timeInSeconds, std::vector<glm::mat4 > &transforms)
		{
			aiMatrix4x4 identity;

			std::cout << "Animation: " << m_scene->mAnimations[0]->mName.C_Str() << std::endl;

			float ticksPerSecond = m_scene->mAnimations[0]->mTicksPerSecond != 0 ?
								m_scene->mAnimations[0]->mTicksPerSecond : 25.0f;
			float timeInTicks = timeInSeconds * ticksPerSecond;
			float animationTime = fmod(timeInTicks, m_scene->mAnimations[0]->mDuration);

			readNodes(0, m_scene->mRootNode, identity);

			transforms.resize(m_numBones);

			for (uint i = 0 ; i < m_numBones ; i++)
			{
				transforms[i] = m_boneInfo[i].finalTransformation;
			}
		}

		const aiNodeAnim *Model::fineNodeAnim(const aiAnimation *anim, const std::string &name)
		{
			for (uint i = 0 ; i < anim->mNumChannels ; i++)
			{
				const aiNodeAnim* pNodeAnim = anim->mChannels[i];
				if (std::string(pNodeAnim->mNodeName.data) == name)
					return pNodeAnim;
			}
			return nullptr;
		}

		void Model::readNodes(float animationTime, const aiNode *node, aiMatrix4x4 &parent)
		{
			std::string nodeName(node->mName.data);

			const aiAnimation *anim = m_scene->mAnimations[0];
			const aiNodeAnim *animNode = fineNodeAnim(anim, node->mName.data);

			aiMatrix4x4 aiFinalBoneTransformation = parent * node->mTransformation;
			glm::mat4 boneTransform = Mathf::assimp_to_glm(node->mTransformation);

		//	if (animNode)
		//	{
		//		aiVector3D Scaling;
		//		ModelAnimation::interpolateNodeScale(Scaling, animationTime, animNode);
		//		glm::mat4 scaling = glm::scale(glm::mat4(1.0f), glm::vec3(Scaling.x, Scaling.y, Scaling.z));
		//
		//		aiQuaternion RotationQ;
		//		ModelAnimation::interpolateNodeRotation(RotationQ, animationTime, animNode);
		//		glm::mat4 rotation = Mat4<float>::mat4FromAssimp(aiMatrix4x4t<float>(RotationQ.GetMatrix()));
		//
		//		aiVector3D Translation;
		//		ModelAnimation::interpolateNodePosition(Translation, animationTime, animNode);
		//		glm::mat4 translation = glm::translate(glm::mat4(1.0f), glm::vec3(Translation.x, Translation.y, Translation.z));
		////		boneTransform = translation * rotation * scaling;
		//	}

			// glm::mat4 finalBoneTransformation = Mathf::assimp_to_glm(aiFinalBoneTransformation);
			// ModelSkeleton::Node *n = new ModelSkeleton::Node();
			// n->name = node->mName.C_Str();
			// n->animatedAbosluteMatrix = finalBoneTransformation;
			// n->parent = p;
			// m_skeleton->addNode(n);

			if (m_boneMapping.find(nodeName) != m_boneMapping.end()) {
				uint BoneIndex = m_boneMapping[nodeName];
				aiMatrix4x4 trs = m_globalInverseTransform * aiFinalBoneTransformation * m_boneInfo[BoneIndex].boneOffset;

		//		glm::mat4 boneOffset = Mathf::assimp_to_glm(m_boneInfo[BoneIndex].boneOffset);
				m_boneInfo[BoneIndex].finalTransformation = Mathf::assimp_to_glm(trs);
			}

			for (std::size_t i = 0; i < node->mNumChildren; i++)
				readNodes(animationTime, node->mChildren[i], aiFinalBoneTransformation);
		}

		void Model::build(int i, std::vector<glm::vec3> &positions, std::vector<glm::vec3> &normals, std::vector<glm::vec2> &uvs, std::vector<VertexBoneData> &bones)
		{
			if (positions.size() != normals.size())
				throw std::runtime_error("Invalid Model !");

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

			std::cout << "Bones: " << bones.size() << std::endl;
			std::cout << "Vertices: " << positions.size() << std::endl;

			m_drawSize[i] = static_cast<GLsizei>(positions.size());

			glGenVertexArrays(1, &m_vao[i]);
			glGenBuffers(1, &m_vbo[i]);
			glGenBuffers(1, &m_ubo[i]);
			glGenBuffers(1, &m_nbo[i]);
			glGenBuffers(1, &m_bbo[i]);
			glGenBuffers(1, &m_wbo[i]);

			std::cout << "LOOOOOL" << std::endl;

			glBindVertexArray(m_vao[i]);

			glEnableVertexAttribArray(0);
			glBindBuffer(GL_ARRAY_BUFFER, m_vbo[i]);
			glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * positions.size() * 3, vBuffer, GL_STATIC_DRAW);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

			glEnableVertexAttribArray(1);
			glBindBuffer(GL_ARRAY_BUFFER, m_nbo[i]);
			glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * normals.size() * 3, nBuffer, GL_STATIC_DRAW);
			glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

			glEnableVertexAttribArray(2);
			glBindBuffer(GL_ARRAY_BUFFER, m_ubo[i]);
			glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * uvs.size() * 2, uBuffer, GL_STATIC_DRAW);
			glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, nullptr);

			glEnableVertexAttribArray(5);
			glBindBuffer(GL_ARRAY_BUFFER, m_bbo[i]);
			glBufferData(GL_ARRAY_BUFFER, sizeof(GLuint) * positions.size() * 4, bBuffer, GL_STATIC_DRAW);
			glVertexAttribIPointer(5, 4, GL_UNSIGNED_INT, 0, nullptr);

			glEnableVertexAttribArray(6);
			glBindBuffer(GL_ARRAY_BUFFER, m_wbo[i]);
			glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * positions.size() * 4, wBuffer, GL_STATIC_DRAW);
			glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, 0, nullptr);

			glBindVertexArray(0);

			delete[] vBuffer;
			delete[] uBuffer;
			delete[] nBuffer;
			delete[] bBuffer;
			delete[] wBuffer;

			std::cout << "LOOOOOL" << std::endl;
		}

		void Model::renderUpdate(void)
		{
			_mat = _gameObject->transform.getMat4();
		}


		void Model::render(void)
		{
		//	static float t = 0;
		//
		//	t++;
		//	std::cout << "m_scene" << m_scene << std::endl;
		//	aiMatrix4x4 identity;
		//	m_skeleton->clearNodes();
		//	loadNode(0, m_scene->mRootNode, identity, nullptr);
		//	m_skeleton->buildMesh();
		//	m_animations->update();

		//
		//	for (int i = 0; i < bone)
		//

			// if (_materials.empty())
			// 	Graphics::Graphics::defaultMaterial->bind(_mat);
			// else

			_materials[0]->bind(_mat);
			// std::cout << "Trs size: " << m_transforms.size() << std::endl;
			for (int i = 0; i < 100; i++)
			{
				std::string uniform = "bonesTransforms[" + std::to_string(i) + "]";
				// _materials[0]->getShader().uniformMat(uniform.c_str(), m_transforms[i]);
				glm::mat4 transform = glm::mat4(1.0);
				_materials[0]->getShader().uniformMat(uniform, transform);
			}

			for (int i = 0; i < m_numMeshes; i++)
			{
				glBindVertexArray(m_vao[i]);
				glDrawArrays(GL_TRIANGLES, 0, m_drawSize[i]);
				glBindVertexArray(0);
			}

			// glDisable(GL_DEPTH_TEST);
			// m_skeleton->render(shader);
			// glEnable(GL_DEPTH_TEST);
		}

		Graphics::AMaterial	*Model::getMaterial(const int &index)
		{
			if (_materials.find(index) == _materials.end())
			{
				std::cerr << "Invalid model material index !" << std::endl;
				exit(1);
			}
			return (_materials[index]);
		}

		Model	&Model::addMaterial(const int &index, Graphics::AMaterial *material)
		{
			std::cout << "Adding: " << material << std::endl;
			_materials[index] = material;
			return (*this);
		}

		nlohmann::json	Model::serialize()
		{
			return nlohmann::json {
				{"componentClass", typeid(Model).name()},
				// {"mesh", _mesh},
				// {"material", _material},
				{"pivot", _mat},
			};
		}

		void Model::deserialize(const nlohmann::json & j)
		{
			// std::cout << this->_sourceFile << "\n";
			// this->_sourceFile = j.at("sourceFile");
			// if (this->_sourceFile != "")
			// 	this->setMesh(this->_sourceFile);
			// this->setMesh(Graphics::Mesh::Deserialize(j.at("mesh")));
			// this->setMaterial(Graphics::AMaterial::Deserialize(j.at("material")));
			// this->_mat = j.at("pivot");
		}

		REGISTER_COMPONENT_CPP(Model)
	}
}