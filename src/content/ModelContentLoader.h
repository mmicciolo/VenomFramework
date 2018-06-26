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
		struct ModelNode {
			std::string nodeName;
			VF::Math::Matrix4 localTransform;
			VF::Math::Matrix4 nodeTransform;
			ModelNode * parent;
			std::vector<ModelNode *> children;
		};
		class ModelContentLoader {
		public:
			template<typename T> VF::Graphics::Model * Load(std::string fileName, VF::Graphics::GraphicsDevice * graphicsDevice);
		protected:
		private:
			std::string fileName;
			VF::Graphics::GraphicsDevice * graphicsDevice;
			VF::Graphics::Texture2D ** textures;
			int textureCount = 0;
			int unamedNodeCount = 0;
			std::vector<VF::Graphics::ModelMesh *> modelMeshes;
			std::map<std::string, ModelNode *> modelNodesMap;
			std::vector<VF::Graphics::Animation> animations;
			VF::Graphics::Model * Import();
			void ImportScene();
			ModelNode * BuildNodeHierarchy(const aiScene * scene, aiNode * node, ModelNode * parent, VF::Math::Matrix4 parentTransform);
			void ImportMaterials(const aiScene * scene);
			void ImportMeshes(const aiScene * scene, aiNode * node, ModelNode * modelNode);
			void ImportAnimations(const aiScene * scene);
			VF::Math::Matrix4 assimpMatrixToVFMatrix(aiMatrix4x4 matrix);
		};
	}
}

#endif