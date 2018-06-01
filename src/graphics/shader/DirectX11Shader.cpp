#include "DirectX11Shader.h"

#ifdef WINDOWS

#include "../device/DirectX11GraphicsDevice.h"
#include "D3Dcompiler.h" 

VF::Graphics::DirectX11Shader::DirectX11Shader(IGraphicsDevice * graphicsDevice, ShaderType::Type shaderType, std::string shaderFile) {
	this->graphicsDevice = graphicsDevice;
	this->shaderType = shaderType;
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
	ID3D10Blob* vertexShaderBuffer;
	HRESULT h = D3DCompileFromFile(std::wstring(shaderFile.begin(), shaderFile.end()).c_str(), NULL, NULL, "ColorVertexShader", "vs_5_0", D3D10_SHADER_ENABLE_STRICTNESS, 0, &vertexShaderBuffer, NULL);
	h = ((ID3D11Device *)((DirectX11GraphicsDevice *)graphicsDevice)->GetDevice())->CreateVertexShader(vertexShaderBuffer->GetBufferPointer(), vertexShaderBuffer->GetBufferSize(), NULL, &vertexShader);
}

void VF::Graphics::DirectX11Shader::LoadPixelShader(std::string shaderFile) {
	ID3D10Blob* pixelShaderBuffer;
	HRESULT h = D3DCompileFromFile(std::wstring(shaderFile.begin(), shaderFile.end()).c_str(), NULL, NULL, "ColorPixelShader", "ps_5_0", D3D10_SHADER_ENABLE_STRICTNESS, 0, &pixelShaderBuffer, NULL);
	h = ((ID3D11Device *)((DirectX11GraphicsDevice *)graphicsDevice)->GetDevice())->CreatePixelShader(pixelShaderBuffer->GetBufferPointer(), pixelShaderBuffer->GetBufferSize(), NULL, &pixelShader);
}

void VF::Graphics::DirectX11Shader::CreateConstantBuffer(int bufferSize) {
	D3D11_BUFFER_DESC matrixBufferDesc;
	matrixBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	matrixBufferDesc.ByteWidth = bufferSize;
	matrixBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	matrixBufferDesc.CPUAccessFlags = 0;
	matrixBufferDesc.MiscFlags = 0;
	matrixBufferDesc.StructureByteStride = 0;

	HRESULT h = ((ID3D11Device *)((DirectX11GraphicsDevice *)graphicsDevice)->GetDevice())->CreateBuffer(&matrixBufferDesc, NULL, &constantBuffer);
}

void VF::Graphics::DirectX11Shader::UpdateConstantBuffer(void * bufferData) {
	((DirectX11GraphicsDevice *)graphicsDevice)->deviceContext->UpdateSubresource(constantBuffer, 0, nullptr, bufferData, 0, 0);
}

void VF::Graphics::DirectX11Shader::Render() {
	switch (shaderType) {
	case ShaderType::Type::VERTEX:
		((DirectX11GraphicsDevice *)graphicsDevice)->deviceContext->VSSetShader(vertexShader, NULL, 0);
		break;
	case ShaderType::Type::PIXEL:
		((DirectX11GraphicsDevice *)graphicsDevice)->deviceContext->PSSetShader(pixelShader, NULL, 0);
		break;
	}
	if (constantBuffer != nullptr) {
		((DirectX11GraphicsDevice *)graphicsDevice)->deviceContext->VSSetConstantBuffers(0, 1, &constantBuffer);
	}
}

#endif