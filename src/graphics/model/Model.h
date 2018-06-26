#ifndef __MODEL_H_
#define __MODEL_H_

#include "../../math/Math.h"
#include "../animation/Animation.h"
#include <vector>
#include <map>

namespace VF {
	namespace Content {
		struct ModelNode;
	}
}

namespace VF {
	namespace Graphics {
		class GraphicsDevice;
		class ModelMesh;
		class Model {
		public:
			Model(GraphicsDevice * graphicsDevice);
			Model(GraphicsDevice * graphicsDevice, std::vector<ModelMesh *> modelMeshes);
			void Draw(VF::Math::Matrix4 projection, VF::Math::Matrix4 view, VF::Math::Matrix4 world);
			std::vector<ModelMesh *> GetModelMeshes() { return modelMeshes; }
			std::map<std::string, VF::Content::ModelNode *> modelNodesMap;
			std::vector<VF::Graphics::Animation> animations;
		protected:
		private:
			GraphicsDevice * graphicsDevice;
			std::vector<ModelMesh *> modelMeshes;
		};
	}
}

#endif