#include "IndexBuffer.h"

VF::Graphics::IndexBuffer::IndexBuffer(GraphicsDevice * graphicsDevice, int indexCount) {
	this->graphicsDevice = graphicsDevice;
	this->indexCount = indexCount;
}

void VF::Graphics::IndexBuffer::SetData(unsigned int * indices) {
	indexBuffer = bgfx::createIndexBuffer(bgfx::makeRef(indices, indexCount * sizeof(unsigned int)), BGFX_BUFFER_INDEX32);
}

void VF::Graphics::IndexBuffer::SetBuffer() {
	bgfx::setIndexBuffer(indexBuffer);
}