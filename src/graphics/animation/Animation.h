#ifndef __ANIMATION_H_
#define __ANIMATION_H_

#include "../../math/Math.h"
#include <string>
#include <vector>

namespace VF {
	namespace Graphics {
		class TranslationKey {
		public:
			TranslationKey(VF::Math::Vector3 position, double time) {
				this->position = position;
				this->time = time;
			}
			VF::Math::Vector3 position;
			double time;
		protected:
		private:
		};

		class RotationKey {
		public:
			RotationKey(VF::Math::Quaternion rotation, double time) {
				this->rotation = rotation;
				this->time = time;
			}
			VF::Math::Quaternion rotation;
			double time;
		protected:
		private:
		};

		class ScaleKey {
		public:
			ScaleKey(VF::Math::Vector3 scale, double time) {
				this->scale = scale;
				this->time = time;
			}
			VF::Math::Vector3 scale;
			double time;
		protected:
		private:
		};

		class Animation {
		public:
			std::string animationName;
			std::vector<TranslationKey> translationKeys;
			std::vector<RotationKey> rotationKeys;
			std::vector<ScaleKey> scaleKeys;
		protected:
		private:
		};
	}
}

#endif