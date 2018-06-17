#include "BasicEffect.h"
#include "../../shader/Shader.h"

#include <bgfx\bgfx.h>
#include <bx\math.h>

VF::Graphics::BasicEffect::BasicEffect() {
	SetupShaders();
}

void VF::Graphics::BasicEffect::SetupShaders() {
	shader = new Shader("vs2.bin", "ps2.bin");
}

void VF::Graphics::BasicEffect::Apply() {
	//bgfx::setViewTransform(0, &parameters.view, &parameters.projection);;
	//bgfx::setTransform(&parameters.world);
	Effect::Apply();
}