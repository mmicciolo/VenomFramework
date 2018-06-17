#ifndef __MODEL_MESH_H_
#define __MODEL_MESH_H_

#include <vector>

namespace VF {
	namespace Graphics {
		class GraphicsDevice;
		class ModelMeshPart;
		class ModelMesh {
		public:
			ModelMesh(GraphicsDevice * graphicsDevice);
			ModelMesh(GraphicsDevice * graphicsDevice, std::vector<ModelMeshPart *> modelMeshParts);
			void Draw();
			std::vector<ModelMeshPart *> modelMeshParts;
		protected:
		private:
			GraphicsDevice * graphicsDevice;
		};
	}
}

#endif