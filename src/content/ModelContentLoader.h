#ifndef __MODEL_CONTENT_LOADER_H_
#define __MODEL_CONTENT_LOADER_H_

#include "ContentLoader.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "../graphics/model/Model.h"
#include "../graphics/model/ModelMesh.h"
#include "../graphics/effect/BasicEffect/BasicEffect.h"
#include "../graphics/buffer/VertexDeclaration.h"

namespace VF {
	namespace Content {
		class ModelContentLoader {
		public:
			template<typename T> T * Load(std::string fileName, VF::Graphics::GraphicsDevice * graphicsDevice) {
				//Assimp::Importer importer;
				//const aiScene * scene = importer.ReadFile(fileName, aiProcessPreset_TargetRealtime_Fast);
				//int i = scene->mMaterials[0]->GetTextureCount(aiTextureType_DIFFUSE);
				//std::vector<VF::Graphics::ModelMesh *> modelMeshes;
				//for (unsigned int i = 0; i < scene->mNumMeshes; i++) {
				//	VF::Graphics::VertexDeclaration ** vertices = new VF::Graphics::VertexDeclaration*[scene->mMeshes[i]->mNumVertices];
				//	for (unsigned int v = 0; v < scene->mMeshes[i]->mNumVertices; v++) {
				//		float x = scene->mMeshes[i]->mVertices[v].x;
				//		float y = scene->mMeshes[i]->mVertices[v].y;
				//		float z = scene->mMeshes[i]->mVertices[v].z;
				//		//vertices[v] = new VF::Graphics::VertexPositionColor(*(new VF::Math::Vector3(x, y, z)), *(new VF::Math::Vector4(1.0f, 1.0f, 1.0f, 1.0f)));
				//	}
				//	VF::Graphics::VertexBuffer * vertexBuffer = new VF::Graphics::VertexBuffer(graphicsDevice, scene->mMeshes[i]->mNumVertices);
				//	vertexBuffer->SetData(vertices);
				//	unsigned int * indices = new unsigned int[scene->mMeshes[i]->mNumFaces * 3];
				//	for (unsigned int f = 0; f < scene->mMeshes[i]->mNumFaces; f++) {
				//		indices[f * 3] = scene->mMeshes[i]->mFaces[f].mIndices[0];
				//		indices[f * 3 + 1] = scene->mMeshes[i]->mFaces[f].mIndices[1];
				//		indices[f * 3 + 2] = scene->mMeshes[i]->mFaces[f].mIndices[2];
				//	}
				//	VF::Graphics::IndexBuffer * indexBuffer = new VF::Graphics::IndexBuffer(graphicsDevice, scene->mMeshes[i]->mNumFaces * 3);
				//	indexBuffer->SetData(indices);
				//	VF::Graphics::ModelMeshPart * modelMeshPart = new VF::Graphics::ModelMeshPart();
				//	modelMeshPart->vertexBuffer = vertexBuffer;
				//	modelMeshPart->indexBuffer = indexBuffer;
				//	modelMeshPart->effect = new VF::Graphics::BasicEffect();
				//	std::vector<VF::Graphics::ModelMeshPart *> modelMeshParts; modelMeshParts.push_back(modelMeshPart);
				//	VF::Graphics::ModelMesh * modelMesh = new VF::Graphics::ModelMesh(graphicsDevice, modelMeshParts);
				//	modelMeshes.push_back(modelMesh);
				//}

				//return new VF::Graphics::Model(graphicsDevice, modelMeshes);

				//std::vector<VF::Graphics::ModelMeshPart *> modelMeshParts; modelMeshParts.push_back(modelMeshPart);
				//VF::Graphics::ModelMesh * modelMesh = new VF::Graphics::ModelMesh(graphicsDevice, modelMeshParts);
				//std::vector<VF::Graphics::ModelMesh *> modelMeshes; modelMeshes.push_back(modelMesh);
				//model = new VF::Graphics::Model(graphicsDevice, modelMeshes);
				return nullptr;
			}
		protected:
		private:
		};
	}
}

#endif