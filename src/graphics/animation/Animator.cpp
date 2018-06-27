#include "Animator.h"
#include "../../content/ModelContentLoader.h"
#include <iostream>

VF::Graphics::Animator::Animator(VF::Graphics::Model * model) {
	this->model = model;
}

void VF::Graphics::Animator::Animate(VF::Content::ModelNode * modelNode, VF::Math::Matrix4 parentTransform, int key) {

	VF::Math::Matrix4 nodeTransform = modelNode->localTransform;

	int keyCount = 150;
	keyCount = key;

	VF::Graphics::Animation * animation = &model->animations[0];

	for (unsigned int i = 0; i < animation->animationChannels.size(); i++) {
		if (modelNode->nodeName == animation->animationChannels[i].animationName) {
			VF::Math::Matrix4 position = VF::Math::translate(VF::Math::Matrix4(1.0f), VF::Math::Vector3(animation->animationChannels[i].translationKeys[keyCount].position.x, animation->animationChannels[i].translationKeys[keyCount].position.y, animation->animationChannels[i].translationKeys[keyCount].position.z));
			VF::Math::Matrix4 rotation = VF::Math::mat4_cast(animation->animationChannels[i].rotationKeys[keyCount].rotation);
			nodeTransform = position * rotation;
			break;
		}
	}

	VF::Math::Matrix4 globalTransform = parentTransform * nodeTransform;

	modelNode->nodeTransform = globalTransform;

	for (unsigned int i = 0; i < modelNode->children.size(); i++) {
		Animate(modelNode->children.at(i), globalTransform, key);
	}
}