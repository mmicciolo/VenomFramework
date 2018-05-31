#ifndef __IVERTEX_BUFFER_
#define __IVERTEX_BUFFER_

#include "IVertexDeclaration.h"
#include "IVertexType.h"
#include "BufferUsage.h"
#include "../device/IGraphicsDevice.h"

namespace VF {
	namespace Graphics {
		class IVertexBuffer {
		public:
			IVertexBuffer() { };
			IVertexBuffer(IGraphicsDevice * graphicsDevice, int vertexCount, IVertexDecleration vertexDecleration, BufferUsage::Usage bufferUsage) { };
			virtual void SetData(IVertexType ** vertices) { };
			//template<class T> void SetData(T * t) { };
			//virtual IVertexDecleration GetVertexDecleration() = 0;
			//virtual BufferUsage::Usage GetBufferUsage() = 0;
		protected:
			IGraphicsDevice * graphicsDevice;
			int vertexCount;
			IVertexDecleration vertexDecleration;
			BufferUsage::Usage bufferUsage;
		private:
		};
	}
}

#endif