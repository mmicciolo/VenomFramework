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
	return new VF::Graphics::Model(graphicsDevice, modelMeshes);
}

void VF::Content::ModelContentLoader::ImportScene() {
	Assimp::Importer importer;
	const aiScene * scene = importer.ReadFile(fileName, aiProcessPreset_TargetRealtime_Fast | aiProcess_MakeLeftHanded | aiProcess_FlipUVs);
	BuildNodeTransformHierarchy(scene, scene->mRootNode, VF::Math::Matrix4(1.0f));
	ImportMaterials(scene);
	ImportNodes(scene);
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

void VF::Content::ModelContentLoader::ImportNodes(const aiScene * scene) {
	ImportNodes(scene, scene->mRootNode, VF::Math::Matrix4(1.0f));
}

void VF::Content::ModelContentLoader::ImportNodes(const aiScene * scene, aiNode * node, VF::Math::Matrix4 parentTransform) {

	VF::Math::Matrix4 globalTransformation = parentTransform * assimpMatrixToVFMatrix(node->mTransformation);

	if (node->mNumMeshes > 0) {
		BoneMaps * boneMaps = ImportBones(scene, node, scene->mMeshes[*node->mMeshes]);
		VF::Graphics::ModelMesh * mesh = ImportMesh(scene->mMeshes[*node->mMeshes], boneMaps);
		if (node->mParent == nullptr) {
			mesh->transform = assimpMatrixToVFMatrix(node->mTransformation);
		}
		else {
			//mesh->transform = assimpMatrixToVFMatrix(node->mTransformation) * assimpMatrixToVFMatrix(node->mParent->mTransformation);
			mesh->transform = nodeTransformHierarchy[node->mName.C_Str()];
			//mesh->transform = globalTransformation;
		}
		modelMeshes.push_back(mesh);
	}

	for (unsigned int i = 0; i < node->mNumChildren; i++) {
		ImportNodes(scene, node->mChildren[i], globalTransformation);
	}
}

VF::Graphics::ModelMesh * VF::Content::ModelContentLoader::ImportMesh(aiMesh * mesh, BoneMaps * boneMaps) {
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
		if (mesh->HasBones()) {
			std::vector<float> weights;
			std::vector<unsigned int> indices;
			unsigned int boneIndex = 0;
			for (unsigned int b = 0; b < mesh->mNumBones; b++) {
				for (unsigned int n = 0; n < mesh->mBones[b]->mNumWeights; n++) {
					if (mesh->mBones[b]->mWeights[n].mVertexId == i) {
						weights.push_back(mesh->mBones[b]->mWeights[n].mWeight);
						indices.push_back(boneMaps->boneIndexMap[std::string(mesh->mBones[b]->mName.data)]);
					}
				}
			}
			weights.resize(4);
			indices.resize(4);
			vertices[i]->addVertexElement(new VF::Graphics::BoneWeightVertexElement(VF::Math::Vector4(weights[0], weights[1], weights[2], weights[3])));
			vertices[i]->addVertexElement(new VF::Graphics::BoneIndexVertexElement(VF::Math::Vector4(indices[0], indices[1], indices[2], indices[3])));
		}
		else {
			vertices[i]->addVertexElement(new VF::Graphics::BoneWeightVertexElement(VF::Math::Vector4(1.0f, 0.0f, 0.0f, 0.0f)));
			vertices[i]->addVertexElement(new VF::Graphics::BoneIndexVertexElement(VF::Math::Vector4(0, 0, 0, 0)));
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

	//if (mesh->HasBones()) {
		effect->parameters.bonesList = boneMaps->bones;
		effect->parameters.boneIndexMap = boneMaps->boneIndexMap;
		effect->parameters.globalTransformation = VF::Math::Matrix4(1.0f);
	//}

	return new VF::Graphics::ModelMesh(graphicsDevice, vertexBuffer, indexBuffer, effect);
}

VF::Content::BoneMaps * VF::Content::ModelContentLoader::ImportBones(const aiScene * scene, aiNode * node, aiMesh * mesh) {
	VF::Content::BoneMaps * boneMaps = new VF::Content::BoneMaps();
	if (mesh->HasBones()) {
		for (unsigned int i = 0; i < mesh->mNumBones; i++) {
			if (boneMaps->boneIndexMap.find(std::string(mesh->mBones[i]->mName.data)) == boneMaps->boneIndexMap.end()) {
				boneMaps->boneIndexMap[std::string(mesh->mBones[i]->mName.data)] = boneMaps->boneIndexMap.size();
				boneMaps->bones.push_back(VF::Graphics::ModelBone(std::string(mesh->mBones[i]->mName.data), assimpMatrixToVFMatrix(mesh->mBones[i]->mOffsetMatrix)));
				boneMaps->bones[boneMaps->bones.size() - 1].transform = nodeTransformHierarchy[std::string(mesh->mBones[i]->mName.data)];
				boneMaps->bones[boneMaps->bones.size() - 1].originalTransform = nodeTransformsMap[std::string(mesh->mBones[i]->mName.data)].originalTransform;
				boneMaps->bones[boneMaps->bones.size() - 1].parentTransform = nodeTransformsMap[std::string(mesh->mBones[i]->mName.data)].parentTransform;
				boneMaps->bones[boneMaps->bones.size() - 1].animations = ImportAnimations(scene, nodeMap[mesh->mBones[i]->mName.data]);
			}
		}
	}
	else {
		boneMaps->bones.push_back(VF::Graphics::ModelBone(std::string(node->mName.data), VF::Math::Matrix4(1.0f)));
		boneMaps->bones[boneMaps->bones.size() - 1].transform = nodeTransformHierarchy[std::string(node->mName.data)];
		boneMaps->bones[boneMaps->bones.size() - 1].originalTransform = nodeTransformsMap[std::string(node->mName.data)].originalTransform;
		boneMaps->bones[boneMaps->bones.size() - 1].parentTransform = nodeTransformsMap[std::string(node->mName.data)].parentTransform;
		boneMaps->bones[boneMaps->bones.size() - 1].animations = ImportAnimations(scene, nodeMap[node->mName.data]);
	}
	return boneMaps;
}

std::vector<VF::Graphics::Animation> VF::Content::ModelContentLoader::ImportAnimations(const aiScene * scene, aiNode * node) {
	std::vector<VF::Graphics::Animation> animations;
	if (scene->HasAnimations()) {
		for (unsigned int i = 0; i < scene->mNumAnimations; i++) {
			aiAnimation * animation = scene->mAnimations[i];
			for (unsigned int i = 0; i < animation->mNumChannels; i++) {
				aiNodeAnim* nodeAnim = animation->mChannels[i];
				if (std::string(nodeAnim->mNodeName.data) == std::string(node->mName.C_Str())) {
					VF::Graphics::Animation animation;
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
					break;
				}
			}
		}
	}
	return animations;
}

VF::Math::Matrix4 VF::Content::ModelContentLoader::assimpMatrixToVFMatrix(aiMatrix4x4 matrix) {
	aiMatrix4x4 m = matrix;
	VF::Math::Matrix4 * m44 = new VF::Math::Matrix4(VF::Math::Vector4(m.a1, m.b1, m.c1, m.d1),
		VF::Math::Vector4(m.a2, m.b2, m.c2, m.d2),
		VF::Math::Vector4(m.a3, m.b3, m.c3, m.d3),
		VF::Math::Vector4(m.a4, m.b4, m.c4, m.d4));
	return *m44;
}

void VF::Content::ModelContentLoader::BuildNodeTransformHierarchy(const aiScene * scene, aiNode * node, VF::Math::Matrix4 parentTransform) {
	VF::Math::Matrix4 nodeTransform = assimpMatrixToVFMatrix(node->mTransformation);
	//aiAnimation * animation = scene->mAnimations[0];
	//aiNodeAnim * nodeAnim = nullptr;
	//for (unsigned int i = 0; i < animation->mNumChannels; i++) {
	//	aiNodeAnim* pNodeAnim = animation->mChannels[i];

	//	if (std::string(pNodeAnim->mNodeName.data) == std::string(node->mName.C_Str())) {
	//		nodeAnim = pNodeAnim;
	//	}
	//}
	//int animKey = 0;
	//if (nodeAnim != nullptr) {
	//	VF::Math::Matrix4 position = VF::Math::translate(VF::Math::Matrix4(1.0f), VF::Math::Vector3(nodeAnim[0].mPositionKeys[animKey].mValue.x, nodeAnim[0].mPositionKeys[animKey].mValue.y, nodeAnim[0].mPositionKeys[animKey].mValue.z));
	//	VF::Math::Matrix4 rotation(assimpMatrixToVFMatrix(aiMatrix4x4(nodeAnim[0].mRotationKeys[animKey].mValue.GetMatrix())));
	//	nodeTransform = position * rotation;
	//}
	if (std::string(node->mName.data) == "") {
		node->mName = std::string("NoName") + std::to_string(unamedNodeCount);
		unamedNodeCount++;
	}
	nodeMap[std::string(node->mName.C_Str())] = node;
	nodeTransformHierarchy[node->mName.C_Str()] = parentTransform * nodeTransform;
	nodeTransformsMap[std::string(node->mName.C_Str())] = { assimpMatrixToVFMatrix(node->mTransformation), parentTransform };
	for (unsigned int i = 0; i < node->mNumChildren; i++) {
		BuildNodeTransformHierarchy(scene, node->mChildren[i], nodeTransformHierarchy[node->mName.C_Str()]);
	}
}