#ifndef __IEFFECT_
#define __IEFFECT_

#include "../../graphics/device/IGraphicsDevice.h"

namespace VF {
	namespace Graphics {
		class IEffect {
		public:
			IEffect() { };
			IEffect(IGraphicsDevice * graphicsDevice) { };
			virtual void Apply() = 0;
		protected:
			IGraphicsDevice * graphicsDevice;
			virtual void SetupShaders() = 0;
		private:
		};
	}
}

#endif