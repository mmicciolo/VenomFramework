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
			IShader(IGraphicsDevice * graphicsDevice, ShaderType::Type shaderType, std::string shaderFile) { };
			virtual void CreateConstantBuffer(int bufferSize) = 0;
			virtual void UpdateConstantBuffer(void * bufferData) = 0;
			virtual void Render() = 0;
			ShaderType::Type GetType() { return shaderType; }
		protected:
			IGraphicsDevice * graphicsDevice;
			ShaderType::Type shaderType;
		private:
		};
	}
}

#endif