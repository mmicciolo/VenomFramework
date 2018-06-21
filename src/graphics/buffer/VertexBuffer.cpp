#include "VertexBuffer.h"
#include "VertexDeclaration.h"

VF::Graphics::VertexBuffer::VertexBuffer(GraphicsDevice * graphicsDevice, int vertexCount) {
	this->graphicsDevice = graphicsDevice;
	this->vertexCount = vertexCount;
}

void VF::Graphics::VertexBuffer::SetData(VertexDeclaration ** vertices) {
	char * vertexDataArray = new char[vertexCount * vertices[0]->GetVertexStride()];
	int byteCount = 0;
	for (int i = 0; i < vertexCount; i++) {
	void * pointer = vertices[i]->ToByteArray();
	memcpy(vertexDataArray + byteCount, pointer, vertices[0]->GetVertexStride());
	delete[] pointer;
	byteCount += vertices[0]->GetVertexStride();
	}

	vertexBuffer = bgfx::createVertexBuffer(bgfx::makeRef(vertexDataArray, vertices[0]->GetVertexStride() * vertexCount), *vertices[0]->vertexDeclaration);
}

void VF::Graphics::VertexBuffer::SetBuffer() {
	bgfx::setVertexBuffer(0, vertexBuffer);
}