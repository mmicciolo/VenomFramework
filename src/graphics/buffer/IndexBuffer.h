#ifndef __INDEX_BUFFER_
#define __INDEX_BUFFER_

#include "../../platform/platform.h"
#include "DirectX11IndexBuffer.h"

namespace VF {
	namespace Graphics {
#ifdef WINDOWS
		typedef VF::Graphics::DirectX11IndexBuffer IndexBuffer;
#endif
	}
}

#endif