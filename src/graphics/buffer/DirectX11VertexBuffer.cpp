#include "DirectX11VertexBuffer.h"
#include<iostream>

VF::Graphics::DirectX11VertexBuffer::DirectX11VertexBuffer(IGraphicsDevice * graphicsDevice, int vertexCount, IVertexDecleration vertexDecleration, BufferUsage::Usage bufferUsage) { 
	this->graphicsDevice = graphicsDevice;
	this->dx11GraphicsDevice = (DirectX11GraphicsDevice *)graphicsDevice;
	this->vertexCount = vertexCount;
	this->vertexDecleration = vertexDecleration;
	this->bufferUsage = bufferUsage;
	
	bufferDescription.Usage = D3D11_USAGE_DEFAULT;
	bufferDescription.ByteWidth = vertexDecleration.vertexStride * vertexCount;
	bufferDescription.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bufferDescription.CPUAccessFlags = 0;
	bufferDescription.MiscFlags = 0;
}

void VF::Graphics::DirectX11VertexBuffer::SetData(IVertexType ** vertices) {
	char * vertexDataArray = new char[vertexCount * vertexDecleration.vertexStride];
	int byteCount = 0;
	for (int i = 0; i < vertexCount; i++) {
		void * pointer = vertices[i]->ToByteArray();
		memcpy(vertexDataArray + byteCount, pointer, vertexDecleration.vertexStride);
		delete [] pointer;
		byteCount += vertexDecleration.vertexStride;
	}
	for (int i = 0; i < vertexCount * vertexDecleration.vertexStride; i++) {
		std::cout << std::hex << (int) vertexDataArray[i] << std::endl;
	}

	// Fill in the subresource data.
	D3D11_SUBRESOURCE_DATA InitData;
	InitData.pSysMem = vertexDataArray;
	InitData.SysMemPitch = 0;
	InitData.SysMemSlicePitch = 0;

	// Create the vertex buffer.
	HRESULT H = ((ID3D11Device *) dx11GraphicsDevice->GetDevice())->CreateBuffer(&bufferDescription, &InitData, &vertexBuffer);

	D3D11_INPUT_ELEMENT_DESC * inputElements = new D3D11_INPUT_ELEMENT_DESC[vertexDecleration.GetVertexElements().size()];

	for (int i = 0; i < vertexDecleration.GetVertexElements().size(); i++) {

		switch (vertexDecleration.GetVertexElements().at(i).vertexElementUsage) {
		case VF::Graphics::VertexElementUsage::Usage::Color:
			inputElements[i].SemanticName = "POSITION";
			break;
		}

		switch (vertexDecleration.GetVertexElements().at(i).vertexElementFormat) {
		case VF::Graphics::VertexElementFormat::Format::Vector3:
			inputElements[i].Format = DXGI_FORMAT_R32G32B32_FLOAT;
			break;
		}

		inputElements[i].SemanticIndex = vertexDecleration.GetVertexElements().at(i).usageIndex;
		inputElements[i].InputSlot = 0;
		inputElements[i].AlignedByteOffset = vertexDecleration.GetVertexElements().at(i).offset;
		inputElements[i].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
		inputElements[i].InstanceDataStepRate = 0;
	}

	HRESULT H = ((ID3D11Device *)dx11GraphicsDevice->GetDevice())->CreateInputLayout(inputElements, vertexDecleration.GetVertexElements().size(), vertexShaderBuffer->GetBufferPointer(), vertexShaderBuffer->GetBufferSize(), &m_layout);
}
