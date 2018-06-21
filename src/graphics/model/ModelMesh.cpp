#include "ModelMesh.h"
#include "../device/GraphicsDevice.h"

VF::Graphics::ModelMesh::ModelMesh(GraphicsDevice * graphicsDevice) {
	this->graphicsDevice = graphicsDevice;
}

VF::Graphics::ModelMesh::ModelMesh(GraphicsDevice * graphicsDevice, VertexBuffer * vertexBuffer, IndexBuffer * indexBuffer, Effect * effect) {
	this->graphicsDevice = graphicsDevice;
	this->vertexBuffer = vertexBuffer;
	this->indexBuffer = indexBuffer;
	this->effect = effect;
}

void VF::Graphics::ModelMesh::Draw() {
	if (indexBuffer == nullptr) {
		graphicsDevice->DrawPrimitives(vertexBuffer, effect);
	}
	else {
		graphicsDevice->DrawIndexedPrimitives(vertexBuffer, indexBuffer, effect);
	}
}