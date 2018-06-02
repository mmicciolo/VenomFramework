#include "VertexPositionColor.h"
#include "../IVertexDeclaration.h"

VF::Graphics::VertexPositionColor::VertexPositionColor() {

}

VF::Graphics::VertexPositionColor::VertexPositionColor(VF::Math::Vector3 position, VF::Math::Vector4 color) {
	this->position = position;
	this->color = color;
}

VF::Graphics::IVertexDecleration VF::Graphics::VertexPositionColor::GetVertexDecleration() {
	std::vector<IVertexElement> * vertexElements = new std::vector<IVertexElement>();
	vertexElements->push_back(*new IVertexElement(0, VertexElementFormat::Format::Vector3, VertexElementUsage::Usage::Position, 0));
	vertexElements->push_back(*new IVertexElement(12, VertexElementFormat::Format::Vector4, VertexElementUsage::Usage::Color, 0));
	return *new IVertexDecleration(*vertexElements);
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