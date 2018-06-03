#include "Camera.h"

VF::Camera::Camera::Camera(PerspectiveProjectionParameters parameters, VF::Math::Vector3 position, VF::Math::Vector3 rotation) {
	this->parameters = parameters;
	this->position = position;
	this->rotation = rotation;
	SetupPerspectiveProjection();
	SetupView();
}

void VF::Camera::Camera::SetupPerspectiveProjection() {
	projectionMatrix = VF::Math::perspectiveFovLH<float>(VF::Math::radians(parameters.fieldOfView), parameters.width, parameters.height, parameters.nearClip, parameters.farClip);
}

void VF::Camera::Camera::SetupView() {
	viewMatrix = VF::Math::lookAtLH(position, position + cameraDirection, cameraUp);
}

void VF::Camera::Camera::SetPerspectiveProjectionParameters(PerspectiveProjectionParameters parameters) {
	parameters = parameters;
	SetupPerspectiveProjection();
}

void VF::Camera::Camera::SetPosition(VF::Math::Vector3 position) {
	this->position = position;
}

void VF::Camera::Camera::SetRotation(VF::Math::Vector3 rotation) {
	this->rotation = rotation;
}

VF::Math::Vector3 VF::Camera::Camera::GetPosition() {
	return position;
}

VF::Math::Vector3 VF::Camera::Camera::GetRotation() {
	return rotation;
}

VF::Math::Matrix4 VF::Camera::Camera::GetProjectionMatrix() {
	return projectionMatrix;
}

VF::Math::Matrix4 VF::Camera::Camera::GetViewMatrix() {
	return viewMatrix;
}

void VF::Camera::Camera::Update() {
	SetupView();
}