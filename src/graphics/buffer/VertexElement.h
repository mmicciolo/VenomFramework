#ifndef __VERTEX_ELEMENT_H_
#define __VERTEX_ELEMENT_H_

#include "../../math/Math.h"

namespace VF {
	namespace Graphics {

		enum VertexElementType {
			POSITION,
			COLOR
		};

		class VertexElement {
		public:
			VertexElementType vertexElementType;
			virtual unsigned int GetSize() { return 0; };
			virtual void * GetData() = 0;
		protected:
		private:
		};

		class PositionVertexElement : public VertexElement {
		public:
			PositionVertexElement(VF::Math::Vector3 position) { this->position = position; vertexElementType = POSITION; }
			unsigned int GetSize() { return 12; }
			void * GetData() { return &position; }
		protected:
		private:
			VF::Math::Vector3 position;
		};

		class ColorVertexElement : public VertexElement {
		public:
			ColorVertexElement(VF::Math::Vector4 color) { this->color = color; vertexElementType = COLOR; }
			unsigned int GetSize() { return 16; }
			void * GetData() { return &color; }
		protected:
		private:
			VF::Math::Vector4 color;
		};
	}
}

#endif