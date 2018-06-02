#ifndef __VERTEX_POSITION_COLOR_
#define __VERTEX_POSITION_COLOR_

#include "../IVertexDeclaration.h"
#include "../IVertexType.h"
#include "../../../math/Math.h"

namespace VF {
	namespace Graphics {
		class VertexPositionColor : public IVertexType {
		public:
			VertexPositionColor();
			VertexPositionColor(VF::Math::Vector3 position, VF::Math::Vector4 color);
			IVertexDecleration GetVertexDecleration();
			void * ToByteArray();
		protected:
		private:
			VF::Math::Vector3 position;
			VF::Math::Vector4 color;
		};
	}
}

#endif