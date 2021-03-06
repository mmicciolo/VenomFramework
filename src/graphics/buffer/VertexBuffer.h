#ifndef __VERTEX_BUFFER_
#define __VERTEX_BUFFER_

#include "../../platform/platform.h"
#include "DirectX11VertexBuffer.h"

namespace VF {
	namespace Graphics {
		#ifdef WINDOWS
		typedef VF::Graphics::DirectX11VertexBuffer VertexBuffer;
		#endif
	}
}

#endif