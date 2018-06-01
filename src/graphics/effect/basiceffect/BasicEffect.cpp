#include "BasicEffect.h"
#include "../../shader/Shader.h"

VF::Graphics::BasicEffect::BasicEffect(IGraphicsDevice * graphicsDevice) {
	this->graphicsDevice = graphicsDevice;
	SetupShaders();
}

void VF::Graphics::BasicEffect::SetupShaders() {
	vertexShader = new Shader(graphicsDevice, VF::Graphics::ShaderType::Type::VERTEX, "BasicEffect.hlsl");
	pixelShader = new Shader(graphicsDevice, VF::Graphics::ShaderType::Type::PIXEL, "BasicEffect.hlsl");
	vertexShader->CreateConstantBuffer(sizeof(parameters));
}

void VF::Graphics::BasicEffect::Apply() {
	vertexShader->UpdateConstantBuffer(&parameters);
	vertexShader->Render();
	pixelShader->Render();
}