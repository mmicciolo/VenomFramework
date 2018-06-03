#include "DirectX11IndexBuffer.h"

#ifdef WINDOWS

#include "../device/DirectX11GraphicsDevice.h"

VF::Graphics::DirectX11IndexBuffer::DirectX11IndexBuffer(IGraphicsDevice * graphicsDevice, int indexCount, BufferUsage::Usage bufferUsage) {
	this->graphicsDevice = graphicsDevice;
	this->indexCount = indexCount;
	this->bufferUsage = bufferUsage;

	bufferDescription.Usage = D3D11_USAGE_DEFAULT;
	bufferDescription.ByteWidth = sizeof(unsigned int) * indexCount;
	bufferDescription.BindFlags = D3D11_BIND_INDEX_BUFFER;
	bufferDescription.CPUAccessFlags = 0;
	bufferDescription.MiscFlags = 0;
}

void VF::Graphics::DirectX11IndexBuffer::SetData(unsigned int * indices) {

	// Fill in the subresource data.
	D3D11_SUBRESOURCE_DATA InitData;
	InitData.pSysMem = indices;
	InitData.SysMemPitch = 0;
	InitData.SysMemSlicePitch = 0;

	// Create the vertex buffer.
	HRESULT H = ((DirectX11GraphicsDevice *) graphicsDevice)->device->CreateBuffer(&bufferDescription, &InitData, &indexBuffer);
}

void VF::Graphics::DirectX11IndexBuffer::SetBuffer() {
	((DirectX11GraphicsDevice *)graphicsDevice)->deviceContext->IASetIndexBuffer(indexBuffer, DXGI_FORMAT_R32_UINT, 0);
}

#endif