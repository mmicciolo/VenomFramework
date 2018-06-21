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
	graphicsDevice->DrawIndexedPrimitives(vertexBuffer, indexBuffer, effect);
}