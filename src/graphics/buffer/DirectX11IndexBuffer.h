#ifndef __DIRECTX11_INDEX_BUFFER_
#define __DIRECTX11_INDEX_BUFFER_

#include "../../platform/platform.h"

#ifdef WINDOWS

#include "IIndexBuffer.h"
#include <d3d11.h>

namespace VF {
	namespace Graphics {
		class DirectX11GraphicsDevice;
		class DirectX11IndexBuffer : public IIndexBuffer {
		public:
			friend VF::Graphics::DirectX11GraphicsDevice;
			DirectX11IndexBuffer(IGraphicsDevice * graphicsDevice, int indexCount, BufferUsage::Usage bufferUsage);
			void SetData(unsigned int * indices);
		protected:
			void SetBuffer();
		private:
			ID3D11Buffer * indexBuffer;
			D3D11_BUFFER_DESC bufferDescription;
		};
	}
}

#endif

#endif