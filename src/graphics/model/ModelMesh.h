#ifndef __MODEL_MESH_H_
#define __MODEL_MESH_H_

#include <vector>
#include "ModelBone.h"

namespace VF {
	namespace Graphics {
		class GraphicsDevice;
		class VertexBuffer;
		class IndexBuffer;
		class Effect;
		class ModelBone;
		class ModelMesh {
		public:
			ModelMesh(GraphicsDevice * graphicsDevice);
			ModelMesh(GraphicsDevice * graphicsDevice, VertexBuffer * vertexBuffer, IndexBuffer * indexBuffer, Effect * effect);
			VertexBuffer * vertexBuffer;
			IndexBuffer * indexBuffer;
			Effect * effect;
			std::vector<ModelBone> bones;
			VF::Math::Matrix4 transform;
			void Draw();
		protected:
		private:
			GraphicsDevice * graphicsDevice;
		};
	}
}

#endif