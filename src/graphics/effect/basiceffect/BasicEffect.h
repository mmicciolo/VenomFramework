#ifndef __BASIC_EFFECT_H_
#define __BASIC_EFFECT_H_

#include "../Effect.h"
#include "../../shader/Shader.h"
#include "../../../math/Math.h"
#include "../../texture/Texture2D.h"

namespace VF {
	namespace Graphics {
		enum VertexDeclarationEnum {
			Position,
			PositionColor,
			PositionColorTexture,
			PositionNormalTexture,
			PositionTexture
		};
		struct BasicEffectParameters {
			VertexDeclarationEnum vertexDeclaration;
			VF::Math::Vector4 diffuseColor;
			VF::Math::Vector4 specularColor;
			VF::Graphics::Texture2D texture;
		};
		class BasicEffect : public Effect {
		public:
			BasicEffect();
			void Apply();
			BasicEffectParameters parameters;
		protected:
			void SetupShaders();
		private:
			bgfx::UniformHandle textureHandle;
		};
	}
}

#endif