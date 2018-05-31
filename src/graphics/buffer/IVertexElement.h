#ifndef __IVERTEX_ELEMENT_
#define __IVERTEX_ELEMENT_

#include "VertexElementFormat.h"
#include "VertexElementUsage.h"

namespace VF {
	namespace Graphics {
		class IVertexElement {
		public:
			IVertexElement() { };
			IVertexElement(int offset, VertexElementFormat::Format vertexElementFormat, VertexElementUsage::Usage vertexElementUsage, int usageIndex) { 
				this->offset = offset;
				this->vertexElementFormat = vertexElementFormat;
				this->vertexElementUsage = vertexElementUsage;
				this->usageIndex = usageIndex;
			};
			//virtual int GetOffset() = 0;
			//virtual VertexElementFormat::Format GetVertexElementFormat() = 0;
			//virtual VertexElementUsage::Usage GetVertexElementUsage() = 0;
			//virtual int GetUsageIndex() = 0;
			int offset;
			VertexElementFormat::Format vertexElementFormat;
			VertexElementUsage::Usage vertexElementUsage;
			int usageIndex;
		protected:

		private:
		};
	}
}

#endif