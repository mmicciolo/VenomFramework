#ifndef __DIRECTX11_GRAPHICS_DEVICE_
#define __DIRECTX11_GRAPHICS_DEVICE_

#include "IGraphicsDevice.h"
#include "../../platform/platform.h"

#ifdef WINDOWS
#include <d3d11.h>
#include <DirectXMath.h>
#include "../buffer/DirectX11VertexBuffer.h"
#include "../shader/DirectX11Shader.h"

namespace VF {
	namespace Graphics {
		class DirectX11GraphicsDevice : public IGraphicsDevice {
		public:
			friend class VF::Graphics::DirectX11VertexBuffer;
			friend class VF::Graphics::DirectX11Shader;
			friend class VF::Graphics::InputLayout;
			DirectX11GraphicsDevice();
			DirectX11GraphicsDevice(VF::Window::IWindow * window);
			void Init();
			void Clear();
			void Present();
			void DrawPrimitives(IVertexBuffer * vertexBuffer, IEffect * effect);
			void DrawIndexedPrimitives();
			void Shutdown();
			void * GetDevice();
		protected:
		private:
			VF::Window::IWindow * window;
			IDXGISwapChain *swapChain;
			ID3D11Device * device;
			ID3D11DeviceContext * deviceContext;
			ID3D11RenderTargetView * backBuffer;
			DXGI_SWAP_CHAIN_DESC scd;
			ID3D11Texture2D * pBackBuffer;
			D3D11_VIEWPORT viewport;
		};
	}
}

#endif

#endif