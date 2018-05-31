#include "VertexPosition.h"
#include "../IVertexDeclaration.h"

VF::Graphics::VertexPosition::VertexPosition() {

}

VF::Graphics::VertexPosition::VertexPosition(VF::Math::Vector3 position) {
	this->position = position;
}

VF::Graphics::IVertexDecleration VF::Graphics::VertexPosition::GetVertexDecleration() {
	std::vector<IVertexElement> * vertexElements = new std::vector<IVertexElement>();
	vertexElements->push_back(* new IVertexElement(0, VertexElementFormat::Format::Vector3, VertexElementUsage::Usage::Position, 0));
	return * new IVertexDecleration(*vertexElements);
}

void * VF::Graphics::VertexPosition::ToByteArray() {
	float * floatArray = new float[3];
	floatArray[0] = position.X;
	floatArray[1] = position.Y;
	floatArray[2] = position.Z;
	return floatArray;
}