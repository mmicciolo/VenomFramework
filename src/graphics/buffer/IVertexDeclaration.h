#ifndef __IVERTEX_DECLERATION_
#define __IVERTEX_DECLERATION_

#include "IVertexElement.h"
#include <vector>

namespace VF {
	namespace Graphics {
		class IVertexDecleration {
		public:
			IVertexDecleration() { };
			IVertexDecleration(std::vector<IVertexElement> vertexElements) { 
				this->vertexElements = vertexElements;
				vertexStride = GetVertexStride(vertexElements);

			};
			//virtual std::vector<IVertexElement> GetVertexElements() = 0;
			int vertexStride;
		protected:
			
			std::vector<IVertexElement> vertexElements;
		private:
			static int GetVertexStride(std::vector<IVertexElement> vertexElements) {
				int max = 0;
				for (size_t i = 0; i < vertexElements.size(); i++)
				{
					int start = vertexElements.at(i).offset + GetVertexElementFormatSize(vertexElements.at(i).vertexElementFormat);
					if (max < start)
						max = start;
				}

				return max;
			}
		};
	}
}

#endif