#ifndef __IVERTEX_TYPE_
#define __IVERTEX_TYPE_

#include "IVertexDeclaration.h"

namespace VF {
	namespace Graphics {
		class IVertexType {
		public:
			virtual IVertexDecleration GetVertexDecleration() = 0;
			virtual void * ToByteArray() = 0;
		protected:
		private:
		};
	}
}

#endif