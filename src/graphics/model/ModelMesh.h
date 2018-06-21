#ifndef __MODEL_MESH_H_
#define __MODEL_MESH_H_

#include <vector>

namespace VF {
	namespace Graphics {
		class GraphicsDevice;
		class VertexBuffer;
		class IndexBuffer;
		class Effect;
		class ModelMesh {
		public:
			ModelMesh(GraphicsDevice * graphicsDevice);
			ModelMesh(GraphicsDevice * graphicsDevice, VertexBuffer * vertexBuffer, IndexBuffer * indexBuffer, Effect * effect);
			VertexBuffer * vertexBuffer;
			IndexBuffer * indexBuffer;
			Effect * effect;
			void Draw();
		protected:
		private:
			GraphicsDevice * graphicsDevice;
		};
	}
}

#endif