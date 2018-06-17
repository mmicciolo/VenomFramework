#ifndef __MODEL_MESH_PART_H_
#define __MODEL_MESH_PART_H_

namespace VF {
	namespace Graphics {
		class VertexBuffer;
		class IndexBuffer;
		class Effect;
		class ModelMeshPart {
		public:
			ModelMeshPart();
			ModelMeshPart(VertexBuffer * vertexBuffer, IndexBuffer * indexBuffer, Effect * effect);
			VertexBuffer * vertexBuffer;
			IndexBuffer * indexBuffer;
			Effect * effect;
		protected:
		private:
		};
	}
}

#endif