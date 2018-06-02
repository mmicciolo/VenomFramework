#ifndef __MOUSE_
#define __MOUSE_

#include "../../window/IWindow.h"

namespace VF {
	namespace Input {
		class Mouse {
		public:
			static void GetState(VF::Window::IWindow * window, MouseState &mouseState);
			static void SetMouseInputMode(VF::Window::IWindow * window, bool capture, bool hidden);
			static void SetMouseCursorPosition(VF::Window::IWindow * window, int x, int y);
		protected:
		private:
			static MouseState mouseState;
		};
	}
}

#endif