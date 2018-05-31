#include "DirectX11GraphicsDevice.h"
#include "../../platform/platform.h"

namespace VF {
	namespace Graphics {
		#ifdef WINDOWS
		typedef DirectX11GraphicsDevice GraphicsDevice;
		#endif
	}
}