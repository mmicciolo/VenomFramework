#ifndef __EFFECT_H_
#define __EFFECT_H_

#include "../shader/Shader.h"

namespace VF {
	namespace Graphics {
		class Effect {
		public:
			Shader * GetShader() { return shader;  }
			virtual void Apply() = 0;
		protected:
			Shader * shader;
		private:
		};
	}
}

#endif