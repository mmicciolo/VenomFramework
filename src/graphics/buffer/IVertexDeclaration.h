#ifndef __IVERTEX_DECLERATION_
#define __IVERTEX_DECLERATION_

#include "IVertexElement.h"
#include <vector>

namespace VF {
	namespace Graphics {
		class IVertexDecleration {
		public:
			IVertexDecleration(std::vector<IVertexElement> vertexElements) { };
			virtual std::vector<IVertexElement> GetVertexElements() = 0;
		protected:
			int vertexStride;
			std::vector<IVertexElement> vertexElements;
		private:
		};
	}
}

#endif