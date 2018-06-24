#include "ModelBone.h"

VF::Graphics::ModelBone::ModelBone() {

}

VF::Graphics::ModelBone::ModelBone(std::string boneName, VF::Math::Matrix4 boneOffset) {
	this->boneName = boneName;
	this->boneOffset = boneOffset;
}