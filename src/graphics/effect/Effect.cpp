#include "Effect.h"

void VF::Graphics::Effect::Apply() {
	bgfx::setViewTransform(0, &projectionViewWorld.view, &projectionViewWorld.projection);;
	bgfx::setTransform(&projectionViewWorld.world);
}