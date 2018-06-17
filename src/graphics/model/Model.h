#ifndef __MODEL_H_
#define __MODEL_H_

#include <vector>

namespace VF {
	namespace Graphics {
		class ModelMesh;
		class Model {
		public:
			Model();
			Model(std::vector<ModelMesh *> modelMeshes);
			Draw();
		protected:
		private:
			std::vector<ModelMesh *> modelMeshes;
		};
	}
}

#endif