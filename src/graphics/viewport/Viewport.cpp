#include "Viewport.h"

VF::Graphics::Viewport::Viewport(int x, int y, int width, int height) {
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
}

VF::Graphics::Viewport::Viewport(int x, int y, int width, int height, float minDepth, float maxDepth) {
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
	this->minDepth = minDepth;
	this->maxDepth = maxDepth;
}

int VF::Graphics::Viewport::GetX() {
	return x;
}

int VF::Graphics::Viewport::GetY() {
	return y;
}

int VF::Graphics::Viewport::GetWidth() {
	return width;
}

int VF::Graphics::Viewport::GetHeight() {
	return height;
}

float VF::Graphics::Viewport::GetMinDepth() {
	return minDepth;
}

float VF::Graphics::Viewport::GetMaxDepth() {
	return maxDepth;
}