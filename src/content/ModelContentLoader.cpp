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
	BuildNodeTransformHierarchy(scene->mRootNode, VF::Math::Matrix4(1.0f));
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
		ImportBones(scene, scene->mMeshes[*node->mMeshes]);
		VF::Graphics::ModelMesh * mesh = ImportMesh(scene->mMeshes[*node->mMeshes]);
		if (node->mParent == nullptr) {
			mesh->transform = assimpMatrixToVFMatrix(node->mTransformation);
		}
		else {
			//mesh->transform = assimpMatrixToVFMatrix(node->mTransformation) * assimpMatrixToVFMatrix(node->mParent->mTransformation);
			//mesh->transform = nodeTransformHierarchy[node->mName.C_Str()];
			mesh->transform = globalTransformation;
		}
		modelMeshes.push_back(mesh);
	}

	for (unsigned int i = 0; i < node->mNumChildren; i++) {
		ImportNodes(scene, node->mChildren[i], globalTransformation);
	}
}

VF::Graphics::ModelMesh * VF::Content::ModelContentLoader::ImportMesh(aiMesh * mesh) {
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
						indices.push_back(boneIndexMap[std::string(mesh->mBones[b]->mName.data)]);
					}
				}
			}
			weights.resize(4);
			indices.resize(4);
			vertices[i]->addVertexElement(new VF::Graphics::BoneWeightVertexElement(VF::Math::Vector4(weights[0], weights[1], weights[2], weights[3])));
			vertices[i]->addVertexElement(new VF::Graphics::BoneIndexVertexElement(VF::Math::Vector4(indices[0], indices[1], indices[2], indices[3])));
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

	if (mesh->HasBones()) {
		effect->parameters.bonesList = bones;
		effect->parameters.boneIndexMap = boneIndexMap;
		effect->parameters.globalTransformation = VF::Math::Matrix4(1.0f);
	}

	return new VF::Graphics::ModelMesh(graphicsDevice, vertexBuffer, indexBuffer, effect);
}

void VF::Content::ModelContentLoader::ImportBones(const aiScene * scene, aiMesh * mesh) {
	if (mesh->HasBones()) {
		for (unsigned int i = 0; i < mesh->mNumBones; i++) {
			if (boneIndexMap.find(std::string(mesh->mBones[i]->mName.data)) == boneIndexMap.end()) {
				boneIndexMap[std::string(mesh->mBones[i]->mName.data)] = boneIndexMap.size();
				bones.push_back(VF::Graphics::ModelBone(std::string(mesh->mBones[i]->mName.data), assimpMatrixToVFMatrix(mesh->mBones[i]->mOffsetMatrix)));
				bones[bones.size() - 1].transform = nodeTransformHierarchy[std::string(mesh->mBones[i]->mName.data)];
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

void VF::Content::ModelContentLoader::BuildNodeTransformHierarchy(aiNode * node, VF::Math::Matrix4 parentTransform) {
	nodeTransformHierarchy[node->mName.C_Str()] = parentTransform * assimpMatrixToVFMatrix(node->mTransformation);
	for (unsigned int i = 0; i < node->mNumChildren; i++) {
		BuildNodeTransformHierarchy(node->mChildren[i], nodeTransformHierarchy[node->mName.C_Str()]);
	}
}