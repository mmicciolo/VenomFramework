#ifndef __DIRECTX11_SHADER_
#define __DIRECTX11_SHADER_

#include "../../platform/platform.h"

#ifdef WINDOWS

#include "IShader.h"
#include <d3d11.h>

namespace VF {
	namespace Graphics {
		class DirectX11Shader : public IShader {
		public:
			DirectX11Shader() { };
			DirectX11Shader(IGraphicsDevice * device, ShaderType::Type shaderType, std::string shaderFile);
		protected:
		private:
			ID3D11VertexShader * vertexShader;
			ID3D11PixelShader * pixelShader;
			void LoadVertexShader(std::string shaderFile);
			void LoadPixelShader(std::string shaderFile);
		};
	}
}

#endif

#endif