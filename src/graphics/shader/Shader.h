#ifndef __SHADER_H_
#define __SHADER_H_

#include <bgfx\bgfx.h>
#include <string>

namespace VF {
	namespace Graphics {
		class Shader {
		public:
			Shader(std::string vsFilename, std::string psFilename);
			bgfx::ProgramHandle programHandle;
		protected:
		private:
			void LoadShaders(std::string vsFilename, std::string psFilename);
			bgfx::ShaderHandle vsHandle;
			bgfx::ShaderHandle psHandle;
		};
	}
}

#endif