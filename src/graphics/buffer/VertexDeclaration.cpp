#include "VertexDeclaration.h"
#include <bgfx\bgfx.h>

VF::Graphics::VertexDeclaration::VertexDeclaration() {
	vertexDeclaration = new bgfx::VertexDecl();
}

VF::Graphics::VertexDeclaration * VF::Graphics::VertexDeclaration::begin() {
	vertexDeclaration->begin();
	return this;
}

VF::Graphics::VertexDeclaration * VF::Graphics::VertexDeclaration::addVertexElement(VertexElement * element) {
	vertexElements.push_back(element);
	switch (element->vertexElementType) {
	case POSITION:
		vertexDeclaration->add(bgfx::Attrib::Position, 3, bgfx::AttribType::Float);
		break;
	case COLOR:
		vertexDeclaration->add(bgfx::Attrib::Color0, 4, bgfx::AttribType::Float);
		break;
	}
	return this;
}

VF::Graphics::VertexDeclaration * VF::Graphics::VertexDeclaration::end() {
	vertexDeclaration->end();
	return this;
}

void * VF::Graphics::VertexDeclaration::ToByteArray() {
	char * vertexData = new char[vertexDeclaration->getStride()];
	unsigned int byteCount = 0;
	for (size_t i = 0; i < vertexElements.size(); i++) {
		memcpy(vertexData + byteCount, vertexElements[i]->GetData(), vertexElements[i]->GetSize());
		byteCount += vertexElements[i]->GetSize();
	}
	return vertexData;
}

unsigned int VF::Graphics::VertexDeclaration::GetVertexStride() {
	return vertexDeclaration->getStride();
}