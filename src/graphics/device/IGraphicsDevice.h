#ifndef __IGRAPHICS_DEVICE_
#define __IGRAPHICS_DEVICE_

#include "../viewport/Viewport.h"
#include "../../window/IWindow.h"

namespace VF {
	namespace Graphics {
		class IVertexBuffer;
		class IGraphicsDevice {
		public:
			IGraphicsDevice() { };
			IGraphicsDevice(VF::Window::IWindow * window) { };
			virtual void Init() = 0;
			virtual void Clear() = 0;
			virtual void Present() = 0;
			virtual void DrawPrimitives(IVertexBuffer * vertexBuffer) = 0;
			virtual void DrawIndexedPrimitives() = 0;
			virtual void Shutdown() = 0;
		protected:
			Viewport * viewPort;
		private:
		};
	}
}

#endif