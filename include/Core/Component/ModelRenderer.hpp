#ifndef BE_CORE_COMPONENT_MODELRENDERER_HPP
#define BE_CORE_COMPONENT_MODELRENDERER_HPP 1

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "Core/Core.hpp"
#include "Component.hpp"
#include "IRender.hpp"
#include "Core/Graphics/MeshBuilder.hpp"

#define VERTEX_BONES_COUNT 4

namespace BeerEngine
{
	namespace Component
	{
		class ModelRenderer : public Component, public IRender
		{
		private:
			struct BoneData
			{
				unsigned int vertexIds[VERTEX_BONES_COUNT];
    			float weights[VERTEX_BONES_COUNT];
			};

		protected:
			std::map<int, Graphics::Mesh*>		_meshes;
			std::map<int, Graphics::AMaterial*>	_materials;
			std::map<Graphics::Mesh*, int>		_materialIndices;
			glm::mat4							_mat;
			std::string							_sourceFile;
			const aiScene						*_assimpScene;

			Graphics::Mesh						_boneDebugView;
			std::vector<BoneData>				_bones;
			GLint								_isModelID;
			GLint								_bonesID;

			void			loadBonesIds();
			void			loadSkeleton();

		public:
			ModelRenderer(GameObject *gameObject);
			ModelRenderer	&load(const std::string &path);
			ModelRenderer	&loadMaterials(Graphics::ShaderProgram *shader);
			Graphics::Mesh	*getMesh(const int &index);
			ModelRenderer	&addMesh(const int &index, Graphics::Mesh *mesh);
			ModelRenderer	&addMaterial(const int &index, Graphics::AMaterial *material);
			Graphics::AMaterial	*getMaterial(const int &index);
			virtual void    renderUpdate(void);
			virtual void    render(void);

			GLenum 			renderMode;

			nlohmann::json	serialize();
			virtual void deserialize(const nlohmann::json & j);

			REGISTER_COMPONENT_HPP
		};
	}
}

#endif
