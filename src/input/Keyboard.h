#ifndef __KEYBOARD_
#define __KEYBOARD_

#include "KeyState.h"
#include "../window/IWindow.h"

namespace VF {
	namespace Input {
		class KeyboardState;

		class Keyboard {
		public:
			static void GetState(VF::Window::IWindow * window, KeyboardState &keyboardState);
		protected:
		private:
			static KeyState::State keyState[256];
		};
	}
}

#endif