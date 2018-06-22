#include "BasicEffect.h"
#include "../../shader/Shader.h"

#include <bgfx\bgfx.h>
#include <bx\math.h>

VF::Graphics::BasicEffect::BasicEffect() {
	SetupShaders();
}

void VF::Graphics::BasicEffect::SetupShaders() {
	shader = new Shader("BasicEffectVS.bin", "BasicEffectPS.bin");
	shader->CreateUniform("vertexDeclaration", bgfx::UniformType::Enum::Int1);
	shader->CreateUniform("diffuseColor", bgfx::UniformType::Enum::Vec4);
	shader->CreateUniform("specularColor", bgfx::UniformType::Enum::Vec4);
	textureHandle = bgfx::createUniform("tex", bgfx::UniformType::Int1);
}

void VF::Graphics::BasicEffect::Apply() {
	Effect::Apply();
	shader->SetUniform("vertexDeclaration", &parameters.vertexDeclaration);
	shader->SetUniform("diffuseColor", &parameters.diffuseColor);
	shader->SetUniform("specularColor", &parameters.specularColor);
	bgfx::setTexture(0, textureHandle, parameters.texture.textureHandle);
}