#ifndef __VERTEX_BUFFER_H_
#define __VERTEX_BUFFER_H_

#include "../device/GraphicsDevice.h"
#include "VertexDeclaration.h"

#include <bgfx\bgfx.h>

//namespace bgfx {
//	struct VertexBufferHandle;
//}

namespace VF {
	namespace Graphics {
		class VertexBuffer {
		public:
			VertexBuffer(GraphicsDevice * graphicsDevice, int vertexCount, VertexDeclaration * vertexDecleration);
			void SetData(VertexDeclaration ** vertices);
			void SetBuffer();
		protected:
		private:
			GraphicsDevice * graphicsDevice;
			bgfx::VertexBufferHandle vertexBuffer;
			int vertexCount;
			VertexDeclaration * vertexDecleration;
		};
	}
}

#endif