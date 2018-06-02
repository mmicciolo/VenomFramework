#include "DirectX11VertexBuffer.h"
#include "../device/DirectX11GraphicsDevice.h"
#include<iostream>

VF::Graphics::DirectX11VertexBuffer::DirectX11VertexBuffer(IGraphicsDevice * graphicsDevice, int vertexCount, IVertexDecleration vertexDecleration, BufferUsage::Usage bufferUsage) { 
	this->graphicsDevice = graphicsDevice;
	this->dx11GraphicsDevice = (DirectX11GraphicsDevice *)graphicsDevice;
	this->vertexCount = vertexCount;
	this->vertexDecleration = vertexDecleration;
	this->bufferUsage = bufferUsage;
	this->inputLayout = new InputLayout(graphicsDevice, vertexDecleration);
	
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
}

void VF::Graphics::DirectX11VertexBuffer::SetBuffer() {
	unsigned int stride = vertexDecleration.vertexStride;
	unsigned int offset = 0;
	((DirectX11GraphicsDevice *)graphicsDevice)->deviceContext->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);
}

void VF::Graphics::DirectX11VertexBuffer::SetInputLayout(IEffect * effect) {
	inputLayout->Apply(effect);
}
