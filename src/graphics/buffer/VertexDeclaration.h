#ifndef __VERTEX_DECLARATION_H_
#define __VERTEX_DECLARATION_H_

#include <vector>
#include "VertexElement.h"

namespace bgfx {
	struct VertexDecl;
}

namespace VF {
	namespace Graphics {
		class VertexDeclaration {
		public:
			VertexDeclaration();
			VertexDeclaration * begin();
			VertexDeclaration * addVertexElement(VertexElement * element);
			VertexDeclaration * end();
			void * ToByteArray();
			unsigned int GetVertexStride();
			std::vector<VertexElement *> vertexElements;
			bgfx::VertexDecl * vertexDeclaration;
		protected:
		private:
		};
	}
}

#endif