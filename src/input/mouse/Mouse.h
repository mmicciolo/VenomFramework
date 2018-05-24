#ifndef __MOUSE_
#define __MOUSE_

#include "../../window/IWindow.h"

namespace VF {
	namespace Input {
		class Mouse {
		public:
			static void GetState(VF::Window::IWindow * window, MouseState &mouseState);
		protected:
		private:
			static MouseState mouseState;
		};
	}
}

#endif