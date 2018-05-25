#ifndef __DIRECTX11_VERTEX_BUFFER_
#define __DIRECTX11_VERTEX_BUFFER_

#include "../../platform/platform.h"

#ifdef WINDOWS

#include <d3d11.h>

namespace VF {
	namespace Graphics {
		class DirectX11VertexBuffer {
		public:
		protected:
		private:
			ID3D11Buffer * vertexBuffer;
		};
	}
}

#endif

#endif