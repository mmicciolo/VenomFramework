#ifndef __GRAPHICS_DEVICE_H_
#define __GRAPHICS_DEVICE_H_

#include "../../window/IWindow.h"
#include "../effect/Effect.h"
#include "../viewport/Viewport.h"
#include <bgfx\bgfx.h>

namespace VF {
	namespace Graphics {
		class VertexBuffer;
		class IndexBuffer;
		class GraphicsDevice {
		public:
			GraphicsDevice(VF::Window::IWindow * window, Viewport viewPort);
			bool Init();
			void Clear();
			void Present();
			void DrawPrimitives(VertexBuffer * vertexBuffer, Effect * effect);
			void DrawIndexedPrimitives(VertexBuffer * vertexBuffer, IndexBuffer * indexBuffer, Effect * effect);
			void Shutdown();
		protected:
		private:
			VF::Window::IWindow * window;
			Viewport viewPort;
		};
	}
}

#endif