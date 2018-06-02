#include "InputLayout.h"

#ifdef WINDOWS
#include "../device/DirectX11GraphicsDevice.h"
#include "../shader/DirectX11Shader.h"
#include "../effect/IEffect.h"

VF::Graphics::InputLayout::InputLayout(IGraphicsDevice * graphicsDevice, IVertexDecleration vertexDecleration) {
	this->graphicsDevice = graphicsDevice;
	this->vertexDecleration = vertexDecleration;
}

void VF::Graphics::InputLayout::Apply(IEffect * effect) {

	if (inputLayout == nullptr) {
		D3D11_INPUT_ELEMENT_DESC * inputElements = new D3D11_INPUT_ELEMENT_DESC[vertexDecleration.GetVertexElements().size()];

		for (int i = 0; i < vertexDecleration.GetVertexElements().size(); i++) {

			switch (vertexDecleration.GetVertexElements().at(i).vertexElementUsage) {
			case VF::Graphics::VertexElementUsage::Usage::Position:
				inputElements[i].SemanticName = "POSITION";
				break;
			case VF::Graphics::VertexElementUsage::Usage::Color:
				inputElements[i].SemanticName = "COLOR";
				break;
			}

			switch (vertexDecleration.GetVertexElements().at(i).vertexElementFormat) {
			case VF::Graphics::VertexElementFormat::Format::Vector3:
				inputElements[i].Format = DXGI_FORMAT_R32G32B32_FLOAT;
				break;
			case VF::Graphics::VertexElementFormat::Format::Vector4:
				inputElements[i].Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
				break;
			}

			inputElements[i].SemanticIndex = vertexDecleration.GetVertexElements().at(i).usageIndex;
			inputElements[i].InputSlot = 0;
			inputElements[i].AlignedByteOffset = vertexDecleration.GetVertexElements().at(i).offset;
			inputElements[i].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
			inputElements[i].InstanceDataStepRate = 0;
		}

		std::vector<IShader *> shaders = effect->GetShaders();
		IShader * vertexShader = nullptr;
		for (int i = 0; i < shaders.size(); i++) {
			if (shaders.at(i)->GetType() == VF::Graphics::ShaderType::Type::VERTEX) {
				vertexShader = shaders.at(i);
			}
		}

		DirectX11Shader * shader = (DirectX11Shader *) vertexShader;

		HRESULT H = ((ID3D11Device *)((DirectX11GraphicsDevice *)graphicsDevice)->GetDevice())->CreateInputLayout(inputElements, vertexDecleration.GetVertexElements().size(), shader->vertexShaderBuffer->GetBufferPointer(), shader->vertexShaderBuffer->GetBufferSize(), &inputLayout);

		((DirectX11GraphicsDevice *)graphicsDevice)->deviceContext->IASetInputLayout(inputLayout);
	}
	else {
		((DirectX11GraphicsDevice *)graphicsDevice)->deviceContext->IASetInputLayout(inputLayout);
	}
}

#endif