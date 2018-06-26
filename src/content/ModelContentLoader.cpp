#include "ModelContentLoader.h"
#include "../graphics/buffer/VertexBuffer.h"
#include "../graphics/buffer/IndexBuffer.h"

template<typename T> VF::Graphics::Model * VF::Content::ModelContentLoader::Load(std::string fileName, VF::Graphics::GraphicsDevice * graphicsDevice) {
	this->fileName = fileName;
	this->graphicsDevice = graphicsDevice;
	return Import();
}

template VF::Graphics::Model * VF::Content::ModelContentLoader::Load<VF::Graphics::Model>(std::string fileName, VF::Graphics::GraphicsDevice * graphicsDevice);

VF::Graphics::Model * VF::Content::ModelContentLoader::Import() {
	ImportScene();
	VF::Graphics::Model * model = new VF::Graphics::Model(graphicsDevice, modelMeshes);
	model->modelNodesMap = modelNodesMap;
	model->animations = animations;
	return model;
}

void VF::Content::ModelContentLoader::ImportScene() {
	Assimp::Importer importer;
	const aiScene * scene = importer.ReadFile(fileName, aiProcessPreset_TargetRealtime_Fast | aiProcess_MakeLeftHanded | aiProcess_FlipUVs);
	ImportMaterials(scene);
	ImportAnimations(scene);
	BuildNodeHierarchy(scene, scene->mRootNode, nullptr, VF::Math::Matrix4(1.0f));
	int r = 0;
}

VF::Content::ModelNode * VF::Content::ModelContentLoader::BuildNodeHierarchy(const aiScene * scene, aiNode * node, ModelNode * parent, VF::Math::Matrix4 parentTransform) {

	if (std::string(node->mName.data) == "") {
		node->mName = std::string("NoName") + std::to_string(unamedNodeCount);
		unamedNodeCount++;
	}

	ModelNode * modelNode = new ModelNode();
	modelNode->nodeName = node->mName.data;
	modelNode->localTransform = assimpMatrixToVFMatrix(node->mTransformation);
	modelNode->nodeTransform = parentTransform * modelNode->localTransform;
	modelNode->parent = parent;

	ImportMeshes(scene, node, modelNode);

	for (unsigned int i = 0; i < node->mNumChildren; i++) {
		modelNode->children.push_back(BuildNodeHierarchy(scene, node->mChildren[i], modelNode, modelNode->nodeTransform));
	}

	modelNodesMap[node->mName.data] = modelNode;

	return modelNode;
}

void VF::Content::ModelContentLoader::ImportMaterials(const aiScene * scene) {
	textures = new VF::Graphics::Texture2D*[scene->mNumMaterials];
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
}

void VF::Content::ModelContentLoader::ImportMeshes(const aiScene * scene, aiNode * node, ModelNode * modelNode) {
	if (node->mNumMeshes > 0) {
		for (unsigned int i = 0; i < node->mNumMeshes; i++) {
			aiMesh * mesh = scene->mMeshes[node->mMeshes[i]];
			VF::Graphics::VertexDeclaration ** vertices = new VF::Graphics::VertexDeclaration*[mesh->mNumVertices];
			for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
				vertices[i] = new VF::Graphics::VertexDeclaration();
				vertices[i]->begin();
				if (mesh->HasPositions()) {
					float x = mesh->mVertices[i].x;
					float y = mesh->mVertices[i].y;
					float z = mesh->mVertices[i].z;
					vertices[i]->addVertexElement(new VF::Graphics::PositionVertexElement(VF::Math::Vector3(x, y, z)));
				}
				if (mesh->HasVertexColors(0)) {
					float r = mesh->mColors[0][i].r;
					float g = mesh->mColors[0][i].g;
					float b = mesh->mColors[0][i].b;
					float a = mesh->mColors[0][i].a;
					vertices[i]->addVertexElement(new VF::Graphics::ColorVertexElement(VF::Math::Vector4(r, g, b, a)));
				}
				if (mesh->HasNormals()) {
					float x = mesh->mVertices[i].x;
					float y = mesh->mVertices[i].y;
					float z = mesh->mVertices[i].z;
					vertices[i]->addVertexElement(new VF::Graphics::NormalVertexElement(VF::Math::Vector3(x, y, z)));
				}
				if (mesh->HasTextureCoords(0)) {
					float x = mesh->mTextureCoords[0][i].x;
					float y = mesh->mTextureCoords[0][i].y;
					vertices[i]->addVertexElement(new VF::Graphics::TextureVertexElement(VF::Math::Vector2(x, y)));
				}
				vertices[i]->end();
			}
			
			VF::Graphics::VertexBuffer * vertexBuffer = new VF::Graphics::VertexBuffer(graphicsDevice, mesh->mNumVertices);
			vertexBuffer->SetData(vertices);
			
			VF::Graphics::IndexBuffer * indexBuffer = nullptr;
			
			if (mesh->HasFaces()) {
				unsigned int * indices = new unsigned int[mesh->mNumFaces * 3];
				for (unsigned int f = 0; f < mesh->mNumFaces; f++) {
					indices[f * 3] = mesh->mFaces[f].mIndices[0];
					indices[f * 3 + 1] = mesh->mFaces[f].mIndices[1];
					indices[f * 3 + 2] = mesh->mFaces[f].mIndices[2];
				}
				indexBuffer = new VF::Graphics::IndexBuffer(graphicsDevice, mesh->mNumFaces * 3);
				indexBuffer->SetData(indices);
			}
			
			VF::Graphics::BasicEffect * effect = new VF::Graphics::BasicEffect();
			
			if (textureCount > 0) {
				effect->parameters.texture = *textures[mesh->mMaterialIndex];
			}
			
			VF::Graphics::ModelMesh * modelMesh = new VF::Graphics::ModelMesh(graphicsDevice, vertexBuffer, indexBuffer, effect);
			modelMesh->modelNode = modelNode;
			modelMeshes.push_back(modelMesh);
		}
	}
}

void VF::Content::ModelContentLoader::ImportAnimations(const aiScene * scene) {
	if (scene->HasAnimations()) {
		for (unsigned int i = 0; i < scene->mNumAnimations; i++) {
			aiAnimation * animation = scene->mAnimations[i];
			for (unsigned int i = 0; i < animation->mNumChannels; i++) {
				aiNodeAnim* nodeAnim = animation->mChannels[i];
				VF::Graphics::Animation animation;
				animation.animationName = nodeAnim->mNodeName.data;
				for (unsigned int n = 0; n < nodeAnim->mNumPositionKeys; n++) {
					animation.translationKeys.push_back(VF::Graphics::TranslationKey(VF::Math::Vector3(nodeAnim->mPositionKeys[n].mValue.x, nodeAnim->mPositionKeys[n].mValue.y, nodeAnim->mPositionKeys[n].mValue.z), nodeAnim->mPositionKeys[n].mTime));
				}
				for (unsigned int n = 0; n < nodeAnim->mNumRotationKeys; n++) {
					animation.rotationKeys.push_back(VF::Graphics::RotationKey(VF::Math::Quaternion(nodeAnim->mRotationKeys[n].mValue.x, nodeAnim->mRotationKeys[n].mValue.y, nodeAnim->mRotationKeys[n].mValue.z, nodeAnim->mRotationKeys[n].mValue.w), nodeAnim->mRotationKeys[n].mTime));
				}
				for (unsigned int n = 0; n < nodeAnim->mNumPositionKeys; n++) {
					animation.scaleKeys.push_back(VF::Graphics::ScaleKey(VF::Math::Vector3(nodeAnim->mScalingKeys[n].mValue.x, nodeAnim->mScalingKeys[n].mValue.y, nodeAnim->mScalingKeys[n].mValue.z), nodeAnim->mScalingKeys[n].mTime));
				}
				animations.push_back(animation);
			}
		}
	}
}

VF::Math::Matrix4 VF::Content::ModelContentLoader::assimpMatrixToVFMatrix(aiMatrix4x4 matrix) {
	aiMatrix4x4 m = matrix;
	VF::Math::Matrix4 * m44 = new VF::Math::Matrix4(VF::Math::Vector4(m.a1, m.b1, m.c1, m.d1),
		VF::Math::Vector4(m.a2, m.b2, m.c2, m.d2),
		VF::Math::Vector4(m.a3, m.b3, m.c3, m.d3),
		VF::Math::Vector4(m.a4, m.b4, m.c4, m.d4));
	return *m44;
}
