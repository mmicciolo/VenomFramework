#include "VertexPositionColor.h"
#include <bgfx\bgfx.h>

VF::Graphics::VertexPositionColor::VertexPositionColor() {
	CreateVertexDeclaration();
}

VF::Graphics::VertexPositionColor::VertexPositionColor(VF::Math::Vector3 position, VF::Math::Vector4 color) {
	this->position = position;
	this->color = color;
	CreateVertexDeclaration();
}

void VF::Graphics::VertexPositionColor::CreateVertexDeclaration() {
	vertexDeclaration = new bgfx::VertexDecl();
	vertexDeclaration->begin()
		.add(bgfx::Attrib::Position, 3, bgfx::AttribType::Float)
		.add(bgfx::Attrib::Color0, 4, bgfx::AttribType::Float, true)
		.end();
}

void * VF::Graphics::VertexPositionColor::ToByteArray() {
	float * floatArray = new float[7];
	floatArray[0] = position.x;
	floatArray[1] = position.y;
	floatArray[2] = position.z;
	floatArray[3] = color.x;
	floatArray[4] = color.y;
	floatArray[5] = color.z;
	floatArray[6] = color.w;
	return floatArray;
}