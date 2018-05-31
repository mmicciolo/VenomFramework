#ifndef __VERTEX_ELEMENT_FORMAT_
#define __VERTEX_ELEMENT_FORMAT_

namespace VF {
	namespace Graphics {
		namespace VertexElementFormat {
			enum Format {
				Single,
				Vector2,
				Vector3,
				Vector4,
				Color
			};


			inline int GetVertexElementFormatSize(VertexElementFormat::Format vertexElementFormat) {
				switch (vertexElementFormat) {
				case VertexElementFormat::Format::Single:
					return 4;
				case VertexElementFormat::Format::Vector2:
					return 8;
				case VertexElementFormat::Format::Vector3:
					return 12;
				case VertexElementFormat::Format::Vector4:
					return 16;
				case VertexElementFormat::Format::Color:
					return 16;
				default:
					return 0;
				}
			}
		}
	}
}

#endif