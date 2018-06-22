#ifndef __TEXTURE_H_
#define __TEXTURE_H_

#include <string>
#include <bgfx\bgfx.h>

namespace VF {
	namespace Graphics {
		class Texture {
		public:
			Texture() { };
			bgfx::TextureHandle textureHandle;
		protected:
			virtual void LoadTexture(std::string fileName) = 0;
		private:
		};
	}
}

#endif