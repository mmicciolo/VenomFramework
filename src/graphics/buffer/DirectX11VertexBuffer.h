#ifndef __DIRECTX11_VERTEX_BUFFER_
#define __DIRECTX11_VERTEX_BUFFER_

#include "../../platform/platform.h"

#ifdef WINDOWS

#include "IVertexBuffer.h"
#include "../device/DirectX11GraphicsDevice.h"

#include <d3d11.h>

namespace VF {
	namespace Graphics {
		class DirectX11VertexBuffer : public IVertexBuffer {
		public:
			DirectX11VertexBuffer() { };
			DirectX11VertexBuffer(IGraphicsDevice * graphicsDevice, int vertexCount, IVertexDecleration vertexDecleration, BufferUsage::Usage bufferUsage);
			void SetData(IVertexType ** vertices);
			//template<class T> void SetData(T * t);
			//IVertexDecleration GetVertexDecleration();
			//BufferUsage::Usage GetBufferUsage();
			ID3D11Buffer * vertexBuffer;
		protected:
		private:
			DirectX11GraphicsDevice * dx11GraphicsDevice;
			D3D11_BUFFER_DESC bufferDescription;
		};
	}
}

#endif

#endif