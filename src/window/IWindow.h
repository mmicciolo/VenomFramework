#ifndef __IWINDOW_
#define __IWINDOW_

#include <vector>
#include "monitor\Monitor.h"
#include "../input/Keyboard/KeyState.h"
#include "../input/mouse/MouseState.h"

namespace VF {
	namespace Input {
		class Keyboard;
		class Mouse;
	}
}

namespace VF {
	namespace Window{
		class IWindowManager;

		class IWindow {
		public:
			friend class VF::Input::Keyboard;
			friend class VF::Input::Mouse;
			virtual void CreateNativeWindow(IWindowManager * windowManager) = 0;
			virtual void Close() = 0;
			virtual long GetWindowHandle() = 0;
			bool IsOpen() { return open; };
			void SetOpen(bool open) { this->open = open; }
		protected:
			int width;
			int height;
			std::string title;
			Monitor monitor;
			bool open;
			VF::Input::KeyState::State keyState[256];
			VF::Input::MouseData mouseData;
		private:
		};
	}
}

#endif