#include "DirectX11Shader.h"

#ifdef WINDOWS

VF::Graphics::DirectX11Shader::DirectX11Shader(IGraphicsDevice * device, ShaderType::Type shaderType, std::string shaderFile) {
	switch (shaderType) {
	case ShaderType::Type::VERTEX:
		LoadVertexShader(shaderFile);
		break;
	case ShaderType::Type::PIXEL:
		LoadPixelShader(shaderFile);
		break;
	}
}

void VF::Graphics::DirectX11Shader::LoadVertexShader(std::string shaderFile) {

}

void VF::Graphics::DirectX11Shader::LoadPixelShader(std::string shaderFile) {

}

#endif