#include "KeyboardState.h"

bool VF::Input::KeyboardState::IsKeyDown(Keys::Key key) {
	return keyState[key] == KeyState::State::Down ? true : false;
}

bool VF::Input::KeyboardState::IsKeyUp(Keys::Key key) {
	return keyState[key] == KeyState::State::Up ? true : false;
}

std::vector<VF::Input::Keys::Key> VF::Input::KeyboardState::GetPressedKeys() {
	return std::vector<Keys::Key>();
}