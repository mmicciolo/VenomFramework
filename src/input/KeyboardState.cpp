#include "KeyboardState.h"

bool KeyboardState::IsKeyDown(Keys::Key key) {
	return keyState[key] == KeyState::State::Down ? true : false;
}

bool KeyboardState::IsKeyUp(Keys::Key key) {
	return keyState[key] == KeyState::State::Up ? true : false;
}

std::vector<Keys::Key> KeyboardState::GetPressedKeys() {
	return std::vector<Keys::Key>();
}