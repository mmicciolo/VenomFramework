#ifndef __INDEX_BUFFER_H_
#define __INDEX_BUFFER_H_

#include <bgfx\bgfx.h>

namespace VF {
	namespace Graphics {
		class GraphicsDevice;
		class IndexBuffer {
		public:
			IndexBuffer(GraphicsDevice * graphicsDevice, int indexCount);
			void SetData(unsigned int * indices);
			int GetIndexCount() { return indexCount; }
			void SetBuffer();
		protected:
		private:
			GraphicsDevice * graphicsDevice;
			bgfx::IndexBufferHandle indexBuffer;
			int indexCount;
		};
	}
}

#endif