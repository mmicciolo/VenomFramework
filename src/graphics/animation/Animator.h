#ifndef __ANIMATOR_H_
#define __ANIMATOR_H_

#include "../model/Model.h"

#include <string>
#include <vector>
#include <map>

namespace VF {
	namespace Content {
		struct ModelNode;
	}
}

namespace VF {
	namespace Graphics {
		class Animator {
		public:
			Animator(VF::Graphics::Model * model);
			void Animate(VF::Content::ModelNode * modelNode, VF::Math::Matrix4 parentTransform);
		protected:
		private:
			VF::Graphics::Model * model;
		};
	}
}

#endif