#include "Keyboard.h"
#include "KeyboardState.h"

void Keyboard::GetState(IWindow * window, KeyboardState &keyboardState) {
	for (int i = 0; i < 256; i++) {
		keyboardState.keyState[i] = window->keyState[i];
	}
}