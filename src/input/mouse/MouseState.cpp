#include "MouseState.h"

bool VF::Input::MouseState::IsButtonPressed(MouseButtons::Buttons button) {
	switch (button) {
	case MouseButtons::Buttons::LEFT_BUTTON:
		return mouseData.leftButton == ButtonState::State::Pressed ? true : false;
	case MouseButtons::Buttons::RIGHT_BUTTON:
		return mouseData.rightButton == ButtonState::State::Pressed ? true : false;
	case MouseButtons::Buttons::MIDDLE_BUTTON:
		return mouseData.middleButton == ButtonState::State::Pressed ? true : false;
	case MouseButtons::Buttons::X_BUTTON_1:
		return mouseData.XButton1 == ButtonState::State::Pressed ? true : false;
	case MouseButtons::Buttons::X_BUTTON_2:
		return mouseData.XButton2 == ButtonState::State::Pressed ? true : false;
	default:
		return false;
	}
}

bool VF::Input::MouseState::IsButtonReleased(MouseButtons::Buttons button) {
	switch (button) {
	case MouseButtons::Buttons::LEFT_BUTTON:
		return mouseData.leftButton == ButtonState::State::Released ? true : false;
	case MouseButtons::Buttons::RIGHT_BUTTON:
		return mouseData.rightButton == ButtonState::State::Released ? true : false;
	case MouseButtons::Buttons::MIDDLE_BUTTON:
		return mouseData.middleButton == ButtonState::State::Released ? true : false;
	case MouseButtons::Buttons::X_BUTTON_1:
		return mouseData.XButton1 == ButtonState::State::Released ? true : false;
	case MouseButtons::Buttons::X_BUTTON_2:
		return mouseData.XButton2 == ButtonState::State::Released ? true : false;
	default:
		return false;
	}
}

VF::Input::MousePosition VF::Input::MouseState::GetMousePosition() {
	return mouseData.position;
}

int VF::Input::MouseState::GetScrollWheelValue() {
	return mouseData.scrollWheelValue;
}