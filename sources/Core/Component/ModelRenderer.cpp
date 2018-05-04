#include "Core/Component/ModelRenderer.hpp"
#include "Core/Graphics/Graphics.hpp"
#include "Core/GameObject.hpp"
#include "Core/Graphics/AMaterial.hpp"
#include "Core/Json/Json.hpp"

namespace BeerEngine
{
	namespace Component
	{
		ModelRenderer::ModelRenderer(GameObject *gameObject) :
			Component(gameObject),
			renderMode(GL_TRIANGLES),
			_assimpScene(nullptr)
		{}

		ModelRenderer	&ModelRenderer::load(const std::string &path)
		{
			Assimp::Importer importer;
			const aiScene *scene = importer.ReadFile(path.c_str(), 
										aiProcess_Triangulate |
										aiProcess_FlipUVs | 
										aiProcess_JoinIdenticalVertices); 
			if (!scene)
			{
				std::cerr << "Invalid model file !" << std::endl;
				exit(EXIT_FAILURE);
			}

			_assimpScene = scene;
			_sourceFile = path;

			bool useTexCoords = false;
			for (std::size_t k = 0; k < scene->mNumMeshes; k++)
			{
				BeerEngine::Graphics::MeshBuilder builder;
				aiMesh *mesh = scene->mMeshes[k];

				std::vector<glm::vec3>	positions;
				std::vector<glm::vec3>	normals;
				std::vector<glm::vec2>	texcoords;
				
				for (std::size_t i = 0; i < mesh->mNumVertices; i++)
				{
					glm::vec3 position;
					position.x = mesh->mVertices[i].x;
					position.y = mesh->mVertices[i].y;
					position.z = mesh->mVertices[i].z;
					positions.push_back(position);

					glm::vec3 normal;
					normal.x = mesh->mNormals[i].x;
					normal.y = mesh->mNormals[i].y;
					normal.z = mesh->mNormals[i].z;
					normals.push_back(normal);

					if(mesh->HasTextureCoords(0))
					{
						useTexCoords = true;
						glm::vec2 texcoord;
						texcoord.x = mesh->mTextureCoords[0][i].x;
						texcoord.y = 1.0 - mesh->mTextureCoords[0][i].y;
						texcoords.push_back(texcoord);
					}
				}

				for (std::size_t i = 0; i < mesh->mNumFaces; i++)
				{
					aiFace face = mesh->mFaces[i];
					for (std::size_t j = 0; j < face.mNumIndices; j++)
					{
						int index = face.mIndices[j];

						glm::vec3 position = positions[index];
						builder.addVertice(position);

						glm::vec3 normal = normals[index];
						builder.addNormal(normal);

						if(mesh->HasTextureCoords(0))
						{
							glm::vec2 texcoord = texcoords[index];
							builder.addUV(texcoord);
						}
					}
				}
				if (useTexCoords)
					builder.calculTangent();
				
				auto builtMesh = builder.build();
				_materialIndices[builtMesh] = mesh->mMaterialIndex;

				builtMesh->setSourcefile(path);
				addMesh(k, builtMesh);
			}
			return (*this);
		}

		ModelRenderer	&ModelRenderer::loadMaterials(Graphics::ShaderProgram *shader)
		{
			std::cout << "Ignoring call to loadMaterials" << std::endl;
			return (*this);

			if (_assimpScene == nullptr)
			{
				std::cerr << "Trying to load materials from a null model !" << std::endl;
				exit(1);
			}
			for (std::size_t i = 0; i < _assimpScene->mNumMaterials; i++)
			{
				const aiMaterial *mat = _assimpScene->mMaterials[i];
				if (mat == nullptr)
				{
					std::cerr << "Null materials !" << std::endl;
					exit(1);
				}
				// auto *material = new BeerEngine::Graphics::AMaterial(shader);

				std::cout << "MAT: " << mat << std::endl;
				std::cout << "MAT tex index: " << aiTextureType_DIFFUSE << std::endl;
				std::cout << "MAT tex index: " << aiGetMaterialTextureCount(mat, aiTextureType_DIFFUSE) << std::endl;
				std::cout << "MAT tex: " << mat->GetTextureCount(aiTextureType_DIFFUSE) << std::endl;
				// {
				// 	std::cout << "LOOOOOOOOOL" << std::endl;
				// 	// aiString texturePath;
				// 	// if (mat->GetTexture(aiTextureType_DIFFUSE, 0, &texturePath, NULL, NULL, NULL, NULL, NULL) == AI_SUCCESS)
				// 	// {
				// 	// 	std::string fullPath = texturePath.data;
				// 	// 	auto *texture = BeerEngine::Graphics::Texture::LoadJPG(fullPath.c_str());
				// 	// 	material->setAlbedo(texture);
				// 	// }
				// }
				// std::cout << "LOOOOOOL " << std::endl;
				// if (mat->GetTextureCount(aiTextureType_NONE ) > 0)
				// 	std::cout << "aiTextureType_NONE " << std::endl;
				// if (mat->GetTextureCount(aiTextureType_DIFFUSE) > 0)
				// 	std::cout << "aiTextureType_DIFFUSE" << std::endl;
				// if (mat->GetTextureCount(aiTextureType_SPECULAR) > 0)
				// 	std::cout << "aiTextureType_SPECULAR" << std::endl;
				// if (mat->GetTextureCount(aiTextureType_AMBIENT) > 0)
				// 	std::cout << "aiTextureType_AMBIENT" << std::endl;
				// if (mat->GetTextureCount(aiTextureType_EMISSIVE) > 0)
				// 	std::cout << "aiTextureType_EMISSIVE" << std::endl;
				// if (mat->GetTextureCount(aiTextureType_HEIGHT) > 0)
				// 	std::cout << "aiTextureType_HEIGHT" << std::endl;
				// if (mat->GetTextureCount(aiTextureType_NORMALS) > 0)
				// 	std::cout << "aiTextureType_NORMALS" << std::endl;
				// if (mat->GetTextureCount(aiTextureType_SHININESS) > 0)
				// 	std::cout << "aiTextureType_SHININESS" << std::endl;
				// if (mat->GetTextureCount(aiTextureType_OPACITY) > 0)
				// 	std::cout << "aiTextureType_OPACITY" << std::endl;
				// if (mat->GetTextureCount(aiTextureType_DISPLACEMENT) > 0)
				// 	std::cout << "aiTextureType_DISPLACEMENT" << std::endl;
				// if (mat->GetTextureCount(aiTextureType_LIGHTMAP) > 0)
				// 	std::cout << "aiTextureType_LIGHTMAP" << std::endl;
				// if (mat->GetTextureCount(aiTextureType_REFLECTION) > 0)
				// 	std::cout << "aiTextureType_REFLECTION" << std::endl;
				// if (mat->GetTextureCount(aiTextureType_UNKNOWN) > 0)
				// 	std::cout << "aiTextureType_UNKNOWN" << std::endl;
				// addMaterial(i, material);
			}
			return (*this);
		}

		Graphics::Mesh	*ModelRenderer::getMesh(const int &index)
		{
			if (_meshes.find(index) == _meshes.end())
			{
				std::cerr << "Invalid model mesh index !" << std::endl;
				exit(1);
			}
			return (_meshes[index]);
		}

		ModelRenderer		&ModelRenderer::addMesh(const int &index, Graphics::Mesh *mesh)
		{
			_meshes[index] = mesh;
			return (*this);
		}

		Graphics::AMaterial	*ModelRenderer::getMaterial(const int &index)
		{
			if (_materials.find(index) == _materials.end())
			{
				std::cerr << "Invalid model material index !" << std::endl;
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

		void    		ModelRenderer::renderUpdate(void)
		{
			_mat = _gameObject->transform.getMat4();
		}

		void    		ModelRenderer::render(void)
		{
			if (_materials.empty())
				Graphics::Graphics::defaultMaterial->bind(_mat);
			for (int i = 0; i < _meshes.size(); i++)
			{
				// if (!_materials.empty())
				// {
				// 	int materialIndex = _materialIndices[_meshes[i]];
				// 	_materials[materialIndex]->bind(_mat);
				// }
				if (!_materials.empty())
					_materials[0]->bind(_mat);
				_meshes[i]->render(renderMode);
			}
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

		void ModelRenderer::deserialize(const nlohmann::json & j)
		{
			std::cout << this->_sourceFile << "\n";
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
