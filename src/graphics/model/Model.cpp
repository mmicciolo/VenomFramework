#include "Model.h"
#include "ModelMesh.h"
#include "../effect/Effect.h"

VF::Graphics::Model::Model(GraphicsDevice * graphicsDevice) {
	this->graphicsDevice = graphicsDevice;
}

VF::Graphics::Model::Model(GraphicsDevice * graphicsDevice, std::vector<ModelMesh *> modelMeshes) {
	this->graphicsDevice = graphicsDevice;
	this->modelMeshes = modelMeshes;
}

void VF::Graphics::Model::Draw(VF::Math::Matrix4 projection, VF::Math::Matrix4 view, VF::Math::Matrix4 world) {
	for (size_t i = 0; i < modelMeshes.size(); i++) {
		modelMeshes.at(i)->effect->projectionViewWorld.projection = projection;
		modelMeshes.at(i)->effect->projectionViewWorld.view = view;
		modelMeshes.at(i)->effect->projectionViewWorld.world = world;
		modelMeshes.at(i)->Draw();
	}
}