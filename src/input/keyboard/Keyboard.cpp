#include "Keyboard.h"
#include "KeyboardState.h"

void VF::Input::Keyboard::GetState(VF::Window::IWindow * window, KeyboardState &keyboardState) {
	for (int i = 0; i < 256; i++) {
		keyboardState.keyState[i] = window->keyState[i];
	}
}