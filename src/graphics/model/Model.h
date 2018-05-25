#ifndef __MODEL_
#define __MODEL_

#include "ModelMesh.h"
#include <vector>

namespace VF {
	namespace Graphics {
		class Model {
		public:
		protected:
		private:
			std::vector<ModelMesh> modelMeshes;
		};
	}
}

#endif