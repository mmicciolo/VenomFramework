#ifndef __EFFECT_H_
#define __EFFECT_H_

#include "../shader/Shader.h"
#include "../../math/Math.h"

namespace VF {
	namespace Graphics {
		struct ProjectionViewWorld {
			VF::Math::Matrix4  world;
			VF::Math::Matrix4 view;
			VF::Math::Matrix4  projection;
		};
		class Effect {
		public:
			Shader * GetShader() { return shader;  }
			void Apply();
			ProjectionViewWorld projectionViewWorld;
		protected:
			Shader * shader;
		private:
		};
	}
}

#endif