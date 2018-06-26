#include "Animator.h"
#include "../../content/ModelContentLoader.h"
#include <iostream>

VF::Graphics::Animator::Animator(VF::Graphics::Model * model) {
	this->model = model;
}

void VF::Graphics::Animator::Animate(VF::Content::ModelNode * modelNode, VF::Math::Matrix4 parentTransform) {

	VF::Math::Matrix4 nodeTransform = modelNode->localTransform;

	int keyCount = 150;

	for (unsigned int i = 0; i < model->animations.size(); i++) {
		if (modelNode->nodeName == model->animations[i].animationName) {
			VF::Math::Matrix4 position = VF::Math::translate(VF::Math::Matrix4(1.0f), VF::Math::Vector3(model->animations[i].translationKeys[keyCount].position.x, model->animations[i].translationKeys[keyCount].position.y, model->animations[i].translationKeys[keyCount].position.z));
			VF::Math::Matrix4 rotation = VF::Math::mat4_cast(model->animations[i].rotationKeys[keyCount].rotation);
			nodeTransform = position;// *rotation;
		}
	}

	std::cout << modelNode->nodeName << std::endl;

	VF::Math::Matrix4 globalTransofrm = parentTransform * nodeTransform;

	if (modelNode->nodeName == "main") {
		int r = 0;
	}

	modelNode->nodeTransform = globalTransofrm;

	for (unsigned int i = 0; i < modelNode->children.size(); i++) {
		Animate(modelNode->children.at(i), globalTransofrm);
	}
}