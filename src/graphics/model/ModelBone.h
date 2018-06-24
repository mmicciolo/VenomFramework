#ifndef __MODEL_BONE_H_
#define __MODEL_BONE_H_

#include "../../math/Math.h"
#include <string>

namespace VF {
	namespace Graphics {
		#define NUM_BONES_PER_VERTEX 4
		class ModelBone {
		public:
			//unsigned int indices[NUM_BONES_PER_VERTEX];
			//float weights[NUM_BONES_PER_VERTEX];
			ModelBone();
			ModelBone(std::string boneName, VF::Math::Matrix4 boneOffset);
			std::string boneName;
			VF::Math::Matrix4 boneOffset;
			VF::Math::Matrix4 finalTransformation;
			VF::Math::Matrix4 transform;
			VF::Math::Matrix4 parentTransform;
		protected:
		private:
		};
	}
}

#endif