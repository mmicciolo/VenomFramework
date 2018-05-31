#include "DirectX11Shader.h"
#include "../../platform/platform.h"

namespace VF {
	namespace Graphics {
#ifdef WINDOWS
		typedef DirectX11Shader Shader;
#endif
	}
}