#ifndef __VERTEX_POSITION_TEXTURE_H_
#define __VERTEX_POSITION_TEXTURE_H_

#include "../VertexDeclaration.h"
#include "../../../math/Math.h"

namespace VF {
	namespace Graphics {
		class VertexPositionTexture : public VertexDeclaration {
		public:
			VertexPositionTexture();
			VertexPositionTexture(VF::Math::Vector3 position, VF::Math::Vector2 texcoords);
			void CreateVertexDeclaration();
			void * ToByteArray();
			int GetVertexStride() { return 20; }
		protected:
		private:
			VF::Math::Vector3 position;
			VF::Math::Vector2 texcoords;
		};
	}
}

#endif