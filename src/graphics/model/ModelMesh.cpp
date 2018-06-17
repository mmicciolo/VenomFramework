#include "ModelMesh.h"
#include "ModelMeshPart.h"
#include "../device/GraphicsDevice.h"

VF::Graphics::ModelMesh::ModelMesh(GraphicsDevice * graphicsDevice) {
	this->graphicsDevice = graphicsDevice;
}

VF::Graphics::ModelMesh::ModelMesh(GraphicsDevice * graphicsDevice, std::vector<ModelMeshPart *> modelMeshParts) {
	this->graphicsDevice = graphicsDevice;
	this->modelMeshParts = modelMeshParts;
}

void VF::Graphics::ModelMesh::Draw() {
	for (size_t i = 0; i < modelMeshParts.size(); i++) {
		graphicsDevice->DrawIndexedPrimitives(modelMeshParts.at(i)->vertexBuffer, modelMeshParts.at(i)->indexBuffer, modelMeshParts.at(i)->effect);
	}
}