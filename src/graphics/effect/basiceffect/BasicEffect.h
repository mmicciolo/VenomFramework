#ifndef __BASIC_EFFECT_H_
#define __BASIC_EFFECT_H_

#include "../Effect.h"
#include "../../shader/Shader.h"
#include "../../../math/Math.h"

namespace VF {
	namespace Graphics {
		struct BasicEffectParameters {
			VF::Math::Matrix4  world;
			VF::Math::Matrix4 view;
			VF::Math::Matrix4  projection;
		};
		class BasicEffect : public Effect {
		public:
			BasicEffect();
			BasicEffectParameters parameters;
			void Apply();
		protected:
			void SetupShaders();
		private:
		};
	}
}

#endif