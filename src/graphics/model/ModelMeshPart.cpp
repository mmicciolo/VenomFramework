#include "ModelMeshPart.h"

VF::Graphics::ModelMeshPart::ModelMeshPart() {

}

VF::Graphics::ModelMeshPart::ModelMeshPart(VertexBuffer * vertexBuffer, IndexBuffer * indexBuffer, Effect * effect) {
	this->vertexBuffer = vertexBuffer;
	this->indexBuffer = indexBuffer;
	this->effect = effect;
}