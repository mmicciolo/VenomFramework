#ifndef __MODEL_H_
#define __MODEL_H_

#include "../../math/Math.h"
#include <vector>

namespace VF {
	namespace Graphics {
		class GraphicsDevice;
		class ModelMesh;
		class Model {
		public:
			Model(GraphicsDevice * graphicsDevice);
			Model(GraphicsDevice * graphicsDevice, std::vector<ModelMesh *> modelMeshes);
			void Draw(VF::Math::Matrix4 projection, VF::Math::Matrix4 view, VF::Math::Matrix4 world);
		protected:
		private:
			GraphicsDevice * graphicsDevice;
			std::vector<ModelMesh *> modelMeshes;
		};
	}
}

#endif