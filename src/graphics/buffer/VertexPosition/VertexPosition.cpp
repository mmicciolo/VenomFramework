#include "VertexPosition.h"
#include <bgfx\bgfx.h>

VF::Graphics::VertexPosition::VertexPosition() {
	CreateVertexDeclaration();
}

VF::Graphics::VertexPosition::VertexPosition(VF::Math::Vector3 position) {
	this->position = position;
	CreateVertexDeclaration();
}

void VF::Graphics::VertexPosition::CreateVertexDeclaration() {
	vertexDeclaration = new bgfx::VertexDecl();
	vertexDeclaration->begin()
		.add(bgfx::Attrib::Position, 3, bgfx::AttribType::Float)
		.end();
}

void * VF::Graphics::VertexPosition::ToByteArray() {
	float * floatArray = new float[3];
	floatArray[0] = position.x;
	floatArray[1] = position.y;
	floatArray[2] = position.z;
	return floatArray;
}