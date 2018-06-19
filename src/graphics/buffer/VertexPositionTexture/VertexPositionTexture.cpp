#include "VertexPositionTexture.h"
#include <bgfx\bgfx.h>

VF::Graphics::VertexPositionTexture::VertexPositionTexture() {
	CreateVertexDeclaration();
}

VF::Graphics::VertexPositionTexture::VertexPositionTexture(VF::Math::Vector3 position, VF::Math::Vector2 texcoords) {
	this->position = position;
	this->texcoords = texcoords;
	CreateVertexDeclaration();
}

void VF::Graphics::VertexPositionTexture::CreateVertexDeclaration() {
	vertexDeclaration = new bgfx::VertexDecl();
	vertexDeclaration->begin()
		.add(bgfx::Attrib::Position, 3, bgfx::AttribType::Float)
		.add(bgfx::Attrib::TexCoord0, 2, bgfx::AttribType::Float, true, true)
		.end();
}

void * VF::Graphics::VertexPositionTexture::ToByteArray() {
	float * floatArray = new float[5];
	floatArray[0] = position.x;
	floatArray[1] = position.y;
	floatArray[2] = position.z;
	floatArray[3] = texcoords.x;
	floatArray[4] = texcoords.y;
	return floatArray;
}