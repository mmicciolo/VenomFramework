#ifndef __IEFFECT_
#define __IEFFECT_

#include "../../graphics/device/IGraphicsDevice.h"
#include "../shader/IShader.h"
#include <vector>

namespace VF {
	namespace Graphics {
		class IEffect {
		public:
			IEffect() { };
			IEffect(IGraphicsDevice * graphicsDevice) { };
			virtual void Apply() = 0;
			std::vector<IShader *> GetShaders() { return shaders; }
		protected:
			IGraphicsDevice * graphicsDevice;
			std::vector<IShader *> shaders;
			virtual void SetupShaders() = 0;
		private:
		};
	}
}

#endif