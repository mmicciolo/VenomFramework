#ifndef __VERTEX_POSITION_COLOR_
#define __VERTEX_POSITION_COLOR_

#include "../VertexDeclaration.h"
#include "../../../math/Math.h"

namespace VF {
	namespace Graphics {
		class VertexPositionColor : public VertexDeclaration {
		public:
			VertexPositionColor();
			VertexPositionColor(VF::Math::Vector3 position, VF::Math::Vector4 color);
			void CreateVertexDeclaration();
			void * ToByteArray();
			int GetVertexStride() { return 28; }
		protected:
		private:
			VF::Math::Vector3 position;
			VF::Math::Vector4 color;
		};
	}
}

#endif