#ifndef __IVERTEX_BUFFER_
#define __IVERTEX_BUFFER_

#include "IVertexDeclaration.h"
#include "BufferUsage.h"

namespace VF {
	namespace Graphics {
		class IVertexBuffer {
		public:
			IVertexBuffer(int vertexCount, IVertexDecleration * vertexDecleration, BufferUsage::Usage bufferUsage) { };
			virtual IVertexDecleration GetVertexDecleration() = 0;
			virtual BufferUsage::Usage GetBufferUsage() = 0;
		protected:
			int vertexCount;
			IVertexDecleration * vertexDecleration;
			BufferUsage::Usage bufferUsage;
		private:
		};
	}
}

#endif