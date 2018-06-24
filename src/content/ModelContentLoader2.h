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
		class ModelContentLoader2 {
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
				
				ImportNodes(scene->mRootNode);
				return nullptr;
			}

			void ImportNodes(aiNode * node) {

				if (node->mNumMeshes > 0) {
					for (unsigned int i = 0; i < node->mNumMeshes; i++) {
						VF::Graphics::VertexDeclaration ** vertices = new VF::Graphics::VertexDeclaration*[node->mMeshes[i]->mNumVertices];
						for (unsigned int v = 0; v < node->mMeshes[i]->mNumVertices; v++) {
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
							if (scene->mMeshes[i]->HasBones()) {
								std::vector<float> weights;
								std::vector<unsigned int> indices;
								unsigned int boneIndex = 0;
								for (unsigned int b = 0; b < scene->mMeshes[i]->mNumBones; b++) {
									for (unsigned int n = 0; n < scene->mMeshes[i]->mBones[b]->mNumWeights; n++) {
										if (scene->mMeshes[i]->mBones[b]->mWeights[n].mVertexId == v) {
											weights.push_back(scene->mMeshes[i]->mBones[b]->mWeights[n].mWeight);
											indices.push_back(boneIndexMap[std::string(scene->mMeshes[i]->mBones[b]->mName.data)]);
										}
									}
								}
								weights.resize(4);
								indices.resize(4);
								vertices[v]->addVertexElement(new VF::Graphics::BoneWeightVertexElement(VF::Math::Vector4(weights[0], weights[1], weights[2], weights[3])));
								vertices[v]->addVertexElement(new VF::Graphics::BoneIndexVertexElement(VF::Math::Vector4(indices[0], indices[1], indices[2], indices[3])));
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

						if (scene->mMeshes[i]->HasBones()) {
							effect->parameters.bonesList = bones;
							effect->parameters.boneIndexMap = boneIndexMap;
							aiMatrix4x4 m = scene->mRootNode->mTransformation;
							VF::Math::Matrix4 * m44 = new VF::Math::Matrix4(VF::Math::Vector4(m.a1, m.b1, m.c1, m.d1),
								VF::Math::Vector4(m.a2, m.b2, m.c2, m.d2),
								VF::Math::Vector4(m.a3, m.b3, m.c3, m.d3),
								VF::Math::Vector4(m.a4, m.b4, m.c4, m.d4));
							effect->parameters.globalTransformation = *m44;
						}

						VF::Graphics::ModelMesh * modelMesh = new VF::Graphics::ModelMesh(graphicsDevice, vertexBuffer, indexBuffer, effect);
						modelMeshes.push_back(modelMesh);
					}
				}

				for (int i = 0; i < node->mNumChildren; i++) {
					ImportNodes(node->mChildren[i]);
				}
			}

			template<typename T> T * Load2(std::string fileName, VF::Graphics::GraphicsDevice * graphicsDevice) {
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
				std::vector<VF::Graphics::ModelBone> bones;
				std::map<std::string, unsigned int> boneIndexMap;

				for (unsigned int i = 0; i < scene->mNumMeshes; i++) {
					for (unsigned int b = 0; b < scene->mMeshes[i]->mNumBones; b++) {
						if (boneIndexMap.find(std::string(scene->mMeshes[i]->mBones[b]->mName.data)) == boneIndexMap.end()) {
							boneIndexMap[std::string(scene->mMeshes[i]->mBones[b]->mName.data)] = boneIndexMap.size();
							//boneIndex = boneIndexMap.size() - 1;
							aiMatrix4x4 m = scene->mMeshes[i]->mBones[b]->mOffsetMatrix;
							VF::Math::Matrix4 * m44 = new VF::Math::Matrix4(VF::Math::Vector4(m.a1, m.b1, m.c1, m.d1),
								VF::Math::Vector4(m.a2, m.b2, m.c2, m.d2),
								VF::Math::Vector4(m.a3, m.b3, m.c3, m.d3),
								VF::Math::Vector4(m.a4, m.b4, m.c4, m.d4));
							bones.push_back(VF::Graphics::ModelBone(std::string(scene->mMeshes[i]->mBones[b]->mName.data), *m44));
						}
						else {
							//boneIndex = boneIndexMap[std::string(scene->mMeshes[i]->mBones[b]->mName.data)];
						}
					}
					//recurse(scene->mRootNode, bones);
					recurse2(scene->mRootNode, VF::Math::Matrix4(1.0f), bones);
					std::cout << scene->mMeshes[i]->mNumBones << std::endl;
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
						if (scene->mMeshes[i]->HasBones()) {
							std::vector<float> weights;
							std::vector<unsigned int> indices;
							unsigned int boneIndex = 0;
							for (unsigned int b = 0; b < scene->mMeshes[i]->mNumBones; b++) {
								for (unsigned int n = 0; n < scene->mMeshes[i]->mBones[b]->mNumWeights; n++) {
									if (scene->mMeshes[i]->mBones[b]->mWeights[n].mVertexId == v) {
										weights.push_back(scene->mMeshes[i]->mBones[b]->mWeights[n].mWeight);
										indices.push_back(boneIndexMap[std::string(scene->mMeshes[i]->mBones[b]->mName.data)]);
									}
								}
							}
							weights.resize(4);
							indices.resize(4);
							vertices[v]->addVertexElement(new VF::Graphics::BoneWeightVertexElement(VF::Math::Vector4(weights[0], weights[1], weights[2], weights[3])));
							vertices[v]->addVertexElement(new VF::Graphics::BoneIndexVertexElement(VF::Math::Vector4(indices[0], indices[1], indices[2], indices[3])));
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

					if (scene->mMeshes[i]->HasBones()) {
						effect->parameters.bonesList = bones;
						effect->parameters.boneIndexMap = boneIndexMap;
						aiMatrix4x4 m = scene->mRootNode->mTransformation;
						VF::Math::Matrix4 * m44 = new VF::Math::Matrix4(VF::Math::Vector4(m.a1, m.b1, m.c1, m.d1),
							VF::Math::Vector4(m.a2, m.b2, m.c2, m.d2),
							VF::Math::Vector4(m.a3, m.b3, m.c3, m.d3),
							VF::Math::Vector4(m.a4, m.b4, m.c4, m.d4));
						effect->parameters.globalTransformation = *m44;
					}
	
					VF::Graphics::ModelMesh * modelMesh = new VF::Graphics::ModelMesh(graphicsDevice, vertexBuffer, indexBuffer, effect);
					modelMeshes.push_back(modelMesh);
				}

				return new VF::Graphics::Model(graphicsDevice, modelMeshes);
			}

			bool ContainsName(std::vector<VF::Graphics::ModelBone> bones, std::string name) {
				for (size_t i = 0; i < bones.size(); i++) {
					if (bones.at(i).boneName == name) {
						return true;
					}
				}
				return false;
			}

			void recurse(aiNode * node, std::vector<VF::Graphics::ModelBone> &bones) {
				for (unsigned int i = 0; i < node->mNumChildren; i++) {
					//std::cout << node->mChildren[i]->mName.C_Str() << std::endl;
					for (int n = 0; n < bones.size(); n++) {
						if (bones[n].boneName == std::string(node->mName.data)) {
							aiMatrix4x4 m = node->mParent->mTransformation;
							VF::Math::Matrix4 * m44 = new VF::Math::Matrix4(VF::Math::Vector4(m.a1, m.b1, m.c1, m.d1),
								VF::Math::Vector4(m.a2, m.b2, m.c2, m.d2),
								VF::Math::Vector4(m.a3, m.b3, m.c3, m.d3),
								VF::Math::Vector4(m.a4, m.b4, m.c4, m.d4));
							bones[n].parentTransform = *m44;
							m = node->mTransformation;
							m44 = new VF::Math::Matrix4(VF::Math::Vector4(m.a1, m.b1, m.c1, m.d1),
								VF::Math::Vector4(m.a2, m.b2, m.c2, m.d2),
								VF::Math::Vector4(m.a3, m.b3, m.c3, m.d3),
								VF::Math::Vector4(m.a4, m.b4, m.c4, m.d4));
							bones[n].transform = *m44;
						}
					}
					recurse(node->mChildren[i], bones);
				}
			}

			void recurse2(aiNode * node, VF::Math::Matrix4 parentTransofrm, std::vector<VF::Graphics::ModelBone> &bones) {
				aiMatrix4x4 m = node->mTransformation;
				VF::Math::Matrix4 * m44 = new VF::Math::Matrix4(VF::Math::Vector4(m.a1, m.b1, m.c1, m.d1),
					VF::Math::Vector4(m.a2, m.b2, m.c2, m.d2),
					VF::Math::Vector4(m.a3, m.b3, m.c3, m.d3),
					VF::Math::Vector4(m.a4, m.b4, m.c4, m.d4));
				VF::Math::Matrix4 globalTransformation = parentTransofrm * *m44;
				for (int n = 0; n < bones.size(); n++) {
					if (bones[n].boneName == std::string(node->mName.data)) {
						bones[n].transform = globalTransformation;
					}
				}

				for (unsigned int i = 0; i < node->mNumChildren; i++) {
					recurse2(node->mChildren[i], globalTransformation, bones);
				}
			}
		protected:
		private:
		};
	}
}

#endif