#ifndef __VERTEX_POSITION_
#define __VERTEX_POSITION_

#include "../IVertexDeclaration.h"
#include "../IVertexType.h"
#include "../../../math/vector3/Vector3.h"

namespace VF {
	namespace Graphics {
		class VertexPosition : public IVertexType {
		public:
			VertexPosition();
			VertexPosition(VF::Math::Vector3 position);
			IVertexDecleration GetVertexDecleration();
			void * ToByteArray();
		protected:
		private:
			VF::Math::Vector3 position;
		};
	}
}

#endif