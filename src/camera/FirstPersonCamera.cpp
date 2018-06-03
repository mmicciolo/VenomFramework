#include "FirstPersonCamera.h"
#include "../input/mouse/Mouse.h"
#include <iostream>
VF::Camera::FirstPersonCamera::FirstPersonCamera(PerspectiveProjectionParameters parameters, VF::Math::Vector3 position, VF::Math::Vector3 rotation) : Camera(parameters, position, rotation) {

}

void VF::Camera::FirstPersonCamera::Update() {
	viewMatrix = VF::Math::lookAtLH(position, position + cameraDirection, cameraUp);
}

void VF::Camera::FirstPersonCamera::Move(VF::Window::IWindow * window, VF::Input::KeyboardState keyboardState, VF::Input::MouseState mouseState) {

	if (firstMouse) {
		if (mouseState.GetMousePosition().x == parameters.width / 2 && mouseState.GetMousePosition().y == parameters.height / 2) {
			firstMouse = false;
		}
	}
	else {
		leftRightRotation -= 0.05f * (parameters.width / 2 - mouseState.GetMousePosition().x);
		upDownRotation -= 0.05f * (mouseState.GetMousePosition().y - parameters.height / 2);
	}

	if (upDownRotation > 90) {
		upDownRotation = 90;
	}
	if (upDownRotation < -90) {
		upDownRotation = 90;
	}

	std::cout << upDownRotation << std::endl;

	VF::Input::Mouse::SetMouseCursorPosition(window, parameters.width / 2, parameters.height / 2);

	VF::Math::Vector3 rotation(0.0f);
	rotation.x = sin(glm::radians(leftRightRotation)) * cos(glm::radians(upDownRotation));
	rotation.y = sin(glm::radians(upDownRotation));
	rotation.z = cos(glm::radians(leftRightRotation)) * cos(glm::radians(upDownRotation));
	cameraDirection = VF::Math::normalize(rotation);

	if (keyboardState.IsKeyDown(VF::Input::Keys::Key::W)) {
		position += cameraDirection * VF::Math::Vector3(0.01f);
	}
	if (keyboardState.IsKeyDown(VF::Input::Keys::Key::S)) {
		position -= cameraDirection * VF::Math::Vector3(0.01f);
	}
	if (keyboardState.IsKeyDown(VF::Input::Keys::Key::A)) {
		position += VF::Math::normalize(VF::Math::cross(cameraDirection, cameraUp)) * VF::Math::Vector3(0.01f);
	}
	if (keyboardState.IsKeyDown(VF::Input::Keys::Key::D)) {
		position -= VF::Math::normalize(VF::Math::cross(cameraDirection, cameraUp)) * VF::Math::Vector3(0.01f);
	}
	if (keyboardState.IsKeyDown(VF::Input::Keys::Key::Left)) {
		leftRightRotation -= 0.01f;
	}
	if (keyboardState.IsKeyDown(VF::Input::Keys::Key::Right)) {
		leftRightRotation += 0.01f;
	}
	if (keyboardState.IsKeyDown(VF::Input::Keys::Key::Up)) {
		upDownRotation += 0.01f;
	}
	if (keyboardState.IsKeyDown(VF::Input::Keys::Key::Down)) {
		upDownRotation -= 0.01f;
	}
}