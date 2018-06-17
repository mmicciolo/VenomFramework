#ifndef __VERTEX_POSITION_
#define __VERTEX_POSITION_

#include "../VertexDeclaration.h"
#include "../../../math/Math.h"

namespace VF {
	namespace Graphics {
		class VertexPosition : public VertexDeclaration {
		public:
			VertexPosition();
			VertexPosition(VF::Math::Vector3 position);
			void CreateVertexDeclaration();
			void * ToByteArray();
			int GetVertexStride() { return 12; };
		protected:
		private:
			VF::Math::Vector3 position;
		};
	}
}

#endif