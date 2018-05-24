#include "Mouse.h"

void VF::Input::Mouse::GetState(VF::Window::IWindow * window, MouseState &mouseState) {
	mouseState.mouseData.position = window->mouseData.position;
	mouseState.mouseData.scrollWheelValue = window->mouseData.scrollWheelValue;
	mouseState.mouseData.leftButton = window->mouseData.leftButton;
	mouseState.mouseData.rightButton = window->mouseData.rightButton;
	mouseState.mouseData.middleButton = window->mouseData.middleButton;
	mouseState.mouseData.XButton1 = window->mouseData.XButton1;
	mouseState.mouseData.XButton2 = window->mouseData.XButton2;
}