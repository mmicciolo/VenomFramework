#ifndef __INPUT_LAYOUT_
#define __INPUT_LAYOUT_

#include "../../platform/platform.h"

#ifdef WINDOWS
#include "IVertexDeclaration.h"
#include "../device/IGraphicsDevice.h"
#include <d3d11.h>

namespace VF {
	namespace Graphics {
		class InputLayout {
		public:
			InputLayout() { };
			InputLayout(IGraphicsDevice * graphicsDevice, IVertexDecleration vertexDecleration);
			void Apply(IEffect * effect);
		protected:
		private:
			IGraphicsDevice * graphicsDevice;
			IVertexDecleration vertexDecleration;
			ID3D11InputLayout * inputLayout;
		};
	}
}

#endif

#endif