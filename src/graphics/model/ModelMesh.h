#ifndef __MODEL_MESH_H_
#define __MODEL_MESH_H_

#include <vector>
#include <map>
#include "ModelBone.h"

namespace VF {
	namespace Content {
		struct ModelNode;
	}
}

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
			std::map<std::string, unsigned int> boneIndexMap;
			std::vector<ModelBone> bones;
			VF::Math::Matrix4 transform;
			VF::Content::ModelNode * modelNode;
			void Draw();
		protected:
		private:
			GraphicsDevice * graphicsDevice;
		};
	}
}

#endif