#ifndef __BASIC_EFFECT_H_
#define __BASIC_EFFECT_H_

#include "../Effect.h"
#include "../../shader/Shader.h"
#include "../../../math/Math.h"
#include "../../texture/Texture2D.h"
#include "../../model/ModelBone.h"
#include <vector>
#include <map>

namespace VF {
	namespace Graphics {
		enum VertexDeclarationEnum {
			Position,
			PositionColor,
			PositionColorTexture,
			PositionNormalTexture,
			PositionTexture,
			Skinned
		};
		struct BasicEffectParameters {
			VertexDeclarationEnum vertexDeclaration;
			VF::Math::Vector4 diffuseColor;
			VF::Math::Vector4 specularColor;
			VF::Graphics::Texture2D texture;
			VF::Math::Matrix4 globalTransformation;
			std::vector<VF::Graphics::ModelBone> bonesList;
			std::map<std::string, unsigned int> boneIndexMap;
			VF::Math::Matrix4 bones[100];
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