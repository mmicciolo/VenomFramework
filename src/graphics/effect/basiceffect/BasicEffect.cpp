#include "BasicEffect.h"
#include "../../shader/Shader.h"

#include <bgfx\bgfx.h>
#include <bx\math.h>

VF::Graphics::BasicEffect::BasicEffect() {
	SetupShaders();
}

void VF::Graphics::BasicEffect::SetupShaders() {
	shader = new Shader("BasicEffectVS.bin", "BasicEffectPS.bin");
	shader->CreateUniform("vertexDeclaration", bgfx::UniformType::Enum::Int1, 1);
	shader->CreateUniform("diffuseColor", bgfx::UniformType::Enum::Vec4, 1);
	shader->CreateUniform("specularColor", bgfx::UniformType::Enum::Vec4, 1);
	shader->CreateUniform("bones", bgfx::UniformType::Enum::Mat4, 100);
	textureHandle = bgfx::createUniform("tex", bgfx::UniformType::Int1);
}

void VF::Graphics::BasicEffect::Apply() {
	Effect::Apply();
	if (parameters.bonesList.size() > 0) {
		parameters.vertexDeclaration = VertexDeclarationEnum::Skinned;
	}
	shader->SetUniform("vertexDeclaration", &parameters.vertexDeclaration, 1);
	shader->SetUniform("diffuseColor", &parameters.diffuseColor, 1);
	shader->SetUniform("specularColor", &parameters.specularColor, 1);
	for (int i = 0; i < parameters.bonesList.size(); i++) {
		int index = parameters.boneIndexMap[parameters.bonesList[i].boneName];
		//VF::Math::Matrix4 globalTrans = parameters.bonesList[i].parentTransform * parameters.bonesList[i].transform;
		//parameters.bones[index] = VF::Math::inverse(parameters.globalTransformation) * parameters.bonesList[i].transform * parameters.bonesList[i].boneOffset;
		VF::Math::Matrix4 nodeTransform = parameters.bonesList[i].parentTransform * parameters.bonesList[i].originalTransform;
		parameters.bones[index] = VF::Math::inverse(parameters.globalTransformation) * nodeTransform * parameters.bonesList[i].boneOffset;
	}
	for (int i = 0; i < 100; i++) {
		//parameters.bones[i] = parameters.globalTransformation * VF::Math::inverse(parameters.globalTransformation) * VF::Math::Matrix4(1.0f);
		//parameters.bones[i] = VF::Math::Matrix4(1.0f);
	}
	shader->SetUniform("bones", &parameters.bones, 100);
	bgfx::setTexture(0, textureHandle, parameters.texture.textureHandle);
}