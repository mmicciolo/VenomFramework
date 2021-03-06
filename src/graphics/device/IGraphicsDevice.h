#ifndef __IGRAPHICS_DEVICE_
#define __IGRAPHICS_DEVICE_

#include "../viewport/Viewport.h"
#include "../../window/IWindow.h"

namespace VF {
	namespace Graphics {
		class IEffect;
		class IVertexBuffer;
		class IIndexBuffer;
		class IGraphicsDevice {
		public:
			IGraphicsDevice() { };
			IGraphicsDevice(VF::Window::IWindow * window) { };
			virtual void Init() = 0;
			virtual void Clear() = 0;
			virtual void Present() = 0;
			virtual void DrawPrimitives(IVertexBuffer * vertexBuffer, IEffect * effect) = 0;
			virtual void DrawIndexedPrimitives(IVertexBuffer * vertexBuffer, IIndexBuffer * indexBuffer, IEffect * effect) = 0;
			virtual void Shutdown() = 0;
		protected:
			Viewport * viewPort;
		private:
		};
	}
}

#endif