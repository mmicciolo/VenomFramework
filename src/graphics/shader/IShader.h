#ifndef __ISHADER_
#define __ISHADER_

#include <string>
#include "../device/IGraphicsDevice.h"
#include "ShaderType.h"

namespace VF{
	namespace Graphics {
		class IShader {
		public:
			IShader() { };
			IShader(IGraphicsDevice * device, ShaderType::Type shaderType, std::string shaderFile) { };
		protected:
			ShaderType::Type shaderType;
		private:
		};
	}
}

#endif