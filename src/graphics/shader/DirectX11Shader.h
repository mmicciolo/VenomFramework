#ifndef __DIRECTX11_SHADER_
#define __DIRECTX11_SHADER_

#include "../../platform/platform.h"

#ifdef WINDOWS

#include "IShader.h"
#include "../buffer/InputLayout.h"
#include <d3d11.h>

namespace VF {
	namespace Graphics {
		class DirectX11Shader : public IShader {
		public:
			friend class VF::Graphics::InputLayout;
			DirectX11Shader() { };
			DirectX11Shader(IGraphicsDevice * graphicsDevice, ShaderType::Type shaderType, std::string shaderFile);
			void CreateConstantBuffer(int bufferSize);
			void UpdateConstantBuffer(void * bufferData);
			void Render();
		protected:
		private:
			ID3D10Blob * vertexShaderBuffer;
			ID3D10Blob * pixelShaderBuffer;
			ID3D11VertexShader * vertexShader;
			ID3D11PixelShader * pixelShader;
			ID3D11Buffer * constantBuffer;
			void LoadVertexShader(std::string shaderFile);
			void LoadPixelShader(std::string shaderFile);
		};
	}
}

#endif

#endif