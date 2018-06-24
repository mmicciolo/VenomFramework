#ifndef __MODEL_CONTENT_LOADER_H_
#define __MODEL_CONTENT_LOADER_H_

#include "ContentLoader.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "../graphics/model/Model.h"
#include "../graphics/model/ModelMesh.h"
#include "../graphics/model/ModelBone.h"
#include "../graphics/effect/BasicEffect/BasicEffect.h"
#include "../graphics/buffer/VertexDeclaration.h"

#include <iostream>
#include <vector>
#include <map>
#include <string>

namespace VF {
	namespace Content {
		class ModelContentLoader {
		public:
			template<typename T> VF::Graphics::Model * Load(std::string fileName, VF::Graphics::GraphicsDevice * graphicsDevice);
		protected:
		private:
			std::string fileName;
			VF::Graphics::GraphicsDevice * graphicsDevice;
			//const aiScene * scene;
			VF::Graphics::Texture2D ** textures;
			int textureCount = 0;
			int unamedNodeCount = 0;
			VF::Graphics::Model * Import();
			void ImportScene();
			void ImportMaterials(const aiScene * scene);
			void ImportNodes(const aiScene * scene);
			void ImportNodes(const aiScene * scene, aiNode * node, VF::Math::Matrix4 parentTransform);
			void ImportBones(const aiScene * scene, aiMesh * mesh);
			void BuildNodeTransformHierarchy(aiNode * node, VF::Math::Matrix4 parentTransform);
			VF::Graphics::ModelMesh * ImportMesh(aiMesh * mesh);
			VF::Math::Matrix4 assimpMatrixToVFMatrix(aiMatrix4x4 matrix);
			std::vector<VF::Graphics::ModelMesh *> modelMeshes;
			std::vector<VF::Graphics::ModelBone> bones;
			std::map<std::string, unsigned int> boneIndexMap;
			std::map<std::string, VF::Math::Matrix4> nodeTransformHierarchy;
		};
	}
}

#endif