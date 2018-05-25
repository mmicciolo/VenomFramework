#ifndef __IVERTEX_ELEMENT_
#define __IVERTEX_ELEMENT_

#include "VertexElementFormat.h"
#include "VertextElementUsage.h"

namespace VF {
	namespace Graphics {
		class IVertexElement {
		public:
			IVertexElement(int offset, VertexElementFormat::Format vertexElementFormat, VertexElementUsage::Usage vertexElementUsage, int usageIndex) { };
			virtual int GetOffset() = 0;
			virtual VertexElementFormat::Format GetVertexElementFormat() = 0;
			virtual VertexElementUsage::Usage GetVertexElementUsage() = 0;
			virtual int GetUsageIndex() = 0;
		protected:
			int offset;
			VertexElementFormat::Format vertexElementFormat;
			VertexElementUsage::Usage vertexElementUsage;
			int usageIndex;
		private:
		};
	}
}

#endif