#include "VertexBuffer.h"

VF::Graphics::VertexBuffer::VertexBuffer(GraphicsDevice * graphicsDevice, int vertexCount, VertexDeclaration * vertexDecleration) {
	this->graphicsDevice = graphicsDevice;
	this->vertexCount = vertexCount;
	this->vertexDecleration = vertexDecleration;
}

void VF::Graphics::VertexBuffer::SetData(VertexDeclaration ** vertices) {
	char * vertexDataArray = new char[vertexCount * vertexDecleration->GetVertexStride()];
	int byteCount = 0;
	for (int i = 0; i < vertexCount; i++) {
		void * pointer = vertices[i]->ToByteArray();
		memcpy(vertexDataArray + byteCount, pointer, vertexDecleration->GetVertexStride());
		delete[] pointer;
		byteCount += vertexDecleration->GetVertexStride();
	}

	vertexBuffer = bgfx::createVertexBuffer(bgfx::makeRef(vertexDataArray, vertexDecleration->GetVertexStride() * vertexCount), *vertexDecleration->getVertexDeclaration());
}

void VF::Graphics::VertexBuffer::SetBuffer() {
	bgfx::setVertexBuffer(0, vertexBuffer);
}