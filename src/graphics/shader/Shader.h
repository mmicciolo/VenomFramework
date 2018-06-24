#ifndef __SHADER_H_
#define __SHADER_H_

#include <bgfx\bgfx.h>
#include <string>
#include <map>

namespace VF {
	namespace Graphics {
		class Shader {
		public:
			Shader(std::string vsFilename, std::string psFilename);
			void CreateUniform(std::string name, bgfx::UniformType::Enum uniformType, unsigned int number);
			void SetUniform(std::string name, void * value, unsigned int number);
			bgfx::ProgramHandle programHandle;
		protected:
		private:
			void LoadShaders(std::string vsFilename, std::string psFilename);
			bgfx::ShaderHandle vsHandle;
			bgfx::ShaderHandle psHandle;
			std::map<std::string, bgfx::UniformHandle> uniforms;
		};
	}
}

#endif