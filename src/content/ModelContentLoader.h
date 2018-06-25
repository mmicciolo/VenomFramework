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
#include "../graphics/animation/Animation.h"

#include <iostream>
#include <vector>
#include <map>
#include <string>

namespace VF {
	namespace Content {
		struct NodeTransforms {
			VF::Math::Matrix4 originalTransform;
			VF::Math::Matrix4 parentTransform;
		};
		struct BoneMaps {
			std::vector<VF::Graphics::ModelBone> bones;
			std::map<std::string, unsigned int> boneIndexMap;
		};
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
			BoneMaps * ImportBones(const aiScene * scene, aiNode * node, aiMesh * mesh);
			std::vector<VF::Graphics::Animation> ImportAnimations(const aiScene * scene, aiNode * node);
			void BuildNodeTransformHierarchy(const aiScene * scene, aiNode * node, VF::Math::Matrix4 parentTransform);
			VF::Graphics::ModelMesh * ImportMesh(aiMesh * mesh, BoneMaps * boneMaps);
			VF::Math::Matrix4 assimpMatrixToVFMatrix(aiMatrix4x4 matrix);
			std::vector<VF::Graphics::ModelMesh *> modelMeshes;
			std::map<std::string, VF::Math::Matrix4> nodeTransformHierarchy;
			std::map<std::string, aiNode *> nodeMap;
			std::map<std::string, NodeTransforms> nodeTransformsMap;
		};
	}
}

#endif