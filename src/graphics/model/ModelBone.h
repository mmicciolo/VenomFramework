#ifndef __MODEL_BONE_H_
#define __MODEL_BONE_H_

#include "../../math/Math.h"
#include "../animation/Animation.h"
#include <string>
#include <vector>

namespace VF {
	namespace Content {
		struct ModelNode;
	}
}

namespace VF {
	namespace Graphics {
		class ModelBone {
		public:
			ModelBone();
			ModelBone(std::string boneName, VF::Math::Matrix4 boneOffset);
			std::string boneName;
			VF::Math::Matrix4 boneOffset;
			VF::Math::Matrix4 originalTransform;
			VF::Math::Matrix4 parentTransform;
			VF::Math::Matrix4 transform;
			std::vector<VF::Graphics::Animation> animations;
			VF::Content::ModelNode * modelNode;
		protected:
		private:
		};
	}
}

#endif