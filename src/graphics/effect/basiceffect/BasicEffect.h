#ifndef __BASIC_EFFECT_H_
#define __BASIC_EFFECT_H_

#include "../Effect.h"
#include "../../shader/Shader.h"
#include "../../../math/Math.h"

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
		};
		class BasicEffect : public Effect {
		public:
			BasicEffect();
			void Apply();
			BasicEffectParameters parameters;
		protected:
			void SetupShaders();
		private:
		};
	}
}

#endif