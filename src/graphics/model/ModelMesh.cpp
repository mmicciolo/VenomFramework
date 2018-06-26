#include "ModelMesh.h"
#include "../device/GraphicsDevice.h"
#include "../../content/ModelContentLoader.h"

VF::Graphics::ModelMesh::ModelMesh(GraphicsDevice * graphicsDevice) {
	this->graphicsDevice = graphicsDevice;
	transform = VF::Math::Matrix4(1.0f);
}

VF::Graphics::ModelMesh::ModelMesh(GraphicsDevice * graphicsDevice, VertexBuffer * vertexBuffer, IndexBuffer * indexBuffer, Effect * effect) {
	this->graphicsDevice = graphicsDevice;
	this->vertexBuffer = vertexBuffer;
	this->indexBuffer = indexBuffer;
	this->effect = effect;
	transform = VF::Math::Matrix4(1.0f);
}

void VF::Graphics::ModelMesh::Draw() {
	effect->projectionViewWorld.world *= modelNode->nodeTransform;
	if (indexBuffer == nullptr) {
		graphicsDevice->DrawPrimitives(vertexBuffer, effect);
	}
	else {
		graphicsDevice->DrawIndexedPrimitives(vertexBuffer, indexBuffer, effect);
	}

}