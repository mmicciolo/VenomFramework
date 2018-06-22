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

#include <iostream>

namespace VF {
	namespace Content {
		class ModelContentLoader {
		public:
			template<typename T> T * Load(std::string fileName, VF::Graphics::GraphicsDevice * graphicsDevice) {
				Assimp::Importer importer;
				const aiScene * scene = importer.ReadFile(fileName, aiProcessPreset_TargetRealtime_Fast | aiProcess_FlipWindingOrder | aiProcess_FlipUVs);
				VF::Graphics::Texture2D ** textures = new VF::Graphics::Texture2D*[scene->mNumMaterials];
				int textureCount = 0;
				for (unsigned int i = 0; i < scene->mNumMaterials; i++) {
					if (scene->mMaterials[i]->GetTextureCount(aiTextureType_DIFFUSE) > 0 ||
						scene->mMaterials[i]->GetTextureCount(aiTextureType_DIFFUSE) > 0 ||
						scene->mMaterials[i]->GetTextureCount(aiTextureType_AMBIENT) > 0 ||
						scene->mMaterials[i]->GetTextureCount(aiTextureType_EMISSIVE) > 0) {
						aiString path;
						if (scene->mMaterials[i]->GetTexture(aiTextureType_DIFFUSE, 0, &path, NULL, NULL, NULL, NULL, NULL) == AI_SUCCESS) {
							textures[i] = new VF::Graphics::Texture2D(path.C_Str());
							textureCount++;
						}
					}
				}

				std::vector<VF::Graphics::ModelMesh *> modelMeshes;
				for (unsigned int i = 0; i < scene->mNumMeshes; i++) {
					VF::Graphics::VertexDeclaration ** vertices = new VF::Graphics::VertexDeclaration*[scene->mMeshes[i]->mNumVertices];
					for (unsigned int v = 0; v < scene->mMeshes[i]->mNumVertices; v++) {
						vertices[v] = new VF::Graphics::VertexDeclaration();
						vertices[v]->begin();
						if (scene->mMeshes[i]->HasPositions()) {
							float x = scene->mMeshes[i]->mVertices[v].x;
							float y = scene->mMeshes[i]->mVertices[v].y;
							float z = scene->mMeshes[i]->mVertices[v].z;
							vertices[v]->addVertexElement(new VF::Graphics::PositionVertexElement(VF::Math::Vector3(x, y, z)));
						}
						if (scene->mMeshes[i]->HasVertexColors(0)) {
							float r = scene->mMeshes[i]->mColors[0][v].r;
							float g = scene->mMeshes[i]->mColors[0][v].g;
							float b = scene->mMeshes[i]->mColors[0][v].b;
							float a = scene->mMeshes[i]->mColors[0][v].a;
							vertices[v]->addVertexElement(new VF::Graphics::ColorVertexElement(VF::Math::Vector4(r, g, b, a)));
						}
						if (scene->mMeshes[i]->HasNormals()) {
							float x = scene->mMeshes[i]->mVertices[v].x;
							float y = scene->mMeshes[i]->mVertices[v].y;
							float z = scene->mMeshes[i]->mVertices[v].z;
							vertices[v]->addVertexElement(new VF::Graphics::NormalVertexElement(VF::Math::Vector3(x, y, z)));
						}
						if (scene->mMeshes[i]->HasTextureCoords(0)) {
							float x = scene->mMeshes[i]->mTextureCoords[0][v].x;
							float y = scene->mMeshes[i]->mTextureCoords[0][v].y;
							vertices[v]->addVertexElement(new VF::Graphics::TextureVertexElement(VF::Math::Vector2(x, y)));
						}
						vertices[v]->end();
					}

					VF::Graphics::VertexBuffer * vertexBuffer = new VF::Graphics::VertexBuffer(graphicsDevice, scene->mMeshes[i]->mNumVertices);
					vertexBuffer->SetData(vertices);

					VF::Graphics::IndexBuffer * indexBuffer = nullptr;

					if (!scene->mMeshes[i]->HasFaces()) {

					}
					else {
						unsigned int * indices = new unsigned int[scene->mMeshes[i]->mNumFaces * 3];
						for (unsigned int f = 0; f < scene->mMeshes[i]->mNumFaces; f++) {
							indices[f * 3] = scene->mMeshes[i]->mFaces[f].mIndices[0];
							indices[f * 3 + 1] = scene->mMeshes[i]->mFaces[f].mIndices[1];
							indices[f * 3 + 2] = scene->mMeshes[i]->mFaces[f].mIndices[2];
						}
						indexBuffer = new VF::Graphics::IndexBuffer(graphicsDevice, scene->mMeshes[i]->mNumFaces * 3);
						indexBuffer->SetData(indices);
					}

					VF::Graphics::BasicEffect * effect = new VF::Graphics::BasicEffect();

					if (textureCount > 0) {
						effect->parameters.texture = *textures[scene->mMeshes[i]->mMaterialIndex];
					}
	
					VF::Graphics::ModelMesh * modelMesh = new VF::Graphics::ModelMesh(graphicsDevice, vertexBuffer, indexBuffer, effect);
					modelMeshes.push_back(modelMesh);
				}

				return new VF::Graphics::Model(graphicsDevice, modelMeshes);
			}
		protected:
		private:
		};
	}
}

#endif