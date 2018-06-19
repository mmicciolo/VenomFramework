#include "VertexPositionNormalTexture.h"
#include <bgfx\bgfx.h>

VF::Graphics::VertexPositionNormalTexture::VertexPositionNormalTexture() {
	CreateVertexDeclaration();
}

VF::Graphics::VertexPositionNormalTexture::VertexPositionNormalTexture(VF::Math::Vector3 position, VF::Math::Vector3 normal, VF::Math::Vector2 texcoords) {
	this->position = position;
	this->normal = normal;
	this->texcoords = texcoords;
	CreateVertexDeclaration();
}

void VF::Graphics::VertexPositionNormalTexture::CreateVertexDeclaration() {
	vertexDeclaration = new bgfx::VertexDecl();
	vertexDeclaration->begin()
		.add(bgfx::Attrib::Position, 3, bgfx::AttribType::Float)
		.add(bgfx::Attrib::Normal, 3, bgfx::AttribType::Float, true, true)
		.add(bgfx::Attrib::TexCoord0, 2, bgfx::AttribType::Float, true, true)
		.end();
}

void * VF::Graphics::VertexPositionNormalTexture::ToByteArray() {
	float * floatArray = new float[8];
	floatArray[0] = position.x;
	floatArray[1] = position.y;
	floatArray[2] = position.z;
	floatArray[3] = normal.x;
	floatArray[4] = normal.y;
	floatArray[5] = normal.z;
	floatArray[6] = texcoords.x;
	floatArray[7] = texcoords.y;
	return floatArray;
}