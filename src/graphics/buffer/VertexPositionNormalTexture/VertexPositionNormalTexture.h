#ifndef __VERTEX_POSITION_NORMAL_TEXTURE_H_
#define __VERTEX_POSITION_NORMAL_TEXTURE_H_

#include "../VertexDeclaration.h"
#include "../../../math/Math.h"

namespace VF {
	namespace Graphics {
		class VertexPositionNormalTexture : public VertexDeclaration {
		public:
			VertexPositionNormalTexture();
			VertexPositionNormalTexture(VF::Math::Vector3 position, VF::Math::Vector3 normal, VF::Math::Vector2 texcoords);
			void CreateVertexDeclaration();
			void * ToByteArray();
			int GetVertexStride() { return 32; }
		protected:
		private:
			VF::Math::Vector3 position;
			VF::Math::Vector3 normal;
			VF::Math::Vector2 texcoords;
		};
	}
}

#endif