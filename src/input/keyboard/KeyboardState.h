#ifndef __KEYBOARD_STATE_
#define __KEYBOARD_STATE_

#include "Keys.h"
#include "KeyState.h"
#include "Keyboard.h"
#include <vector>

namespace VF {
	namespace Input {
		class KeyboardState {
		public:
			friend class Keyboard;
			bool IsKeyDown(Keys::Key key);
			bool IsKeyUp(Keys::Key key);
			std::vector<Keys::Key> GetPressedKeys();
		protected:
		private:
			KeyState::State keyState[256];
		};
	}
}

#endif