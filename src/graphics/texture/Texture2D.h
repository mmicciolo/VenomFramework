#ifndef __TEXTURE_2D_H_
#define __TEXTURE_2D_H_

#include "Texture.h"
#include <bx\bx.h>
#include <bx\math.h>
#include <bx\file.h>
#include <bimg\bimg.h>
#include <bimg\decode.h>

namespace VF {
	namespace Graphics {
		class Texture2D : public Texture {
		public:
			Texture2D() { }
			Texture2D(std::string fileName);
		protected:
			void LoadTexture(std::string fileName);
		private:
			static void imageReleaseCb(void* _ptr, void* _userData)
			{
				BX_UNUSED(_ptr);
				bimg::ImageContainer* imageContainer = (bimg::ImageContainer*)_userData;
				bimg::imageFree(imageContainer);
			}
			bx::AllocatorI* getDefaultAllocator()
			{
				BX_PRAGMA_DIAGNOSTIC_PUSH();
				BX_PRAGMA_DIAGNOSTIC_IGNORED_MSVC(4459); // warning C4459: declaration of 's_allocator' hides global declaration
				BX_PRAGMA_DIAGNOSTIC_IGNORED_CLANG_GCC("-Wshadow");
				static bx::DefaultAllocator s_allocator;
				return &s_allocator;
				BX_PRAGMA_DIAGNOSTIC_POP();
			}
		};
	}
}

#endif