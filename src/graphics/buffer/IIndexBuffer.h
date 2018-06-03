#ifndef __IINDEX_BUFFER_
#define __IINDEX_BUFFER_

#include "../device/IGraphicsDevice.h"
#include "BufferUsage.h"

namespace VF {
	namespace Graphics {
		class IIndexBuffer {
		public:
			IIndexBuffer() { };
			IIndexBuffer(IGraphicsDevice * graphicsDevice, int indexCount, BufferUsage::Usage bufferUsage) { };
			virtual void SetData(unsigned int * indices) = 0;
			int GetIndexCount() { return indexCount; }
		protected:
			virtual void SetBuffer() { };
			IGraphicsDevice * graphicsDevice;
			int indexCount;
			BufferUsage::Usage bufferUsage;
		private:
		};
	}
}

#endif