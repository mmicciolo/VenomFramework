#ifndef __BASIC_EFFECT_
#define __BASIC_EFFECT_

#include "../IEffect.h"
#include "../../shader/IShader.h"
#include "../../device/IGraphicsDevice.h"
#include "../../../math/Math.h"

namespace VF {
	namespace Graphics {
		struct BasicEffectParameters {
			VF::Math::Matrix4  world;
			VF::Math::Matrix4 view;
			VF::Math::Matrix4  projection;
		};
		class BasicEffect : public IEffect {
		public:
			BasicEffect(IGraphicsDevice * graphicsDevice);
			void Apply();
			BasicEffectParameters parameters;
			IShader * vertexShader;
			IShader * pixelShader;
		protected:
			void SetupShaders();
		private:
		};
	}
}

#endif