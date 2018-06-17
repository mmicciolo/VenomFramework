#ifndef __MODEL_MESH_H_
#define __MODEL_MESH_H_

#include <vector>

namespace VF {
	namespace Graphics {
		class ModelMeshPart;
		class ModelMesh {
		public:
			ModelMesh();
			ModelMesh(std::vector<ModelMeshPart *> modelMeshParts);
			Draw();
		protected:
		private:
			std::vector<ModelMeshPart *> modelMeshParts;
		};
	}
}

#endif