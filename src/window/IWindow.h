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
			virtual void SetWindowTitle(std::string title) = 0;
			virtual void SetWindowIcon() = 0;
			virtual void SetWindowPosition(int x, int y) = 0;
			virtual void SetWindowSize(int width, int height) = 0;
			virtual void HideWindow(bool hide) = 0;
			virtual void EnableFullscreen() = 0;
			virtual void DisableFullscreen() = 0;
			virtual void CreateNativeWindow(IWindowManager * windowManager) = 0;
			virtual void Close() = 0;
			virtual void * GetWindowHandle() = 0;
			virtual Monitor * GetMonitor() { return &monitor; };
			bool IsOpen() { return open; };
			void SetOpen(bool open) { this->open = open; }
			int x;
			int y;
			int width;
			int height;
		protected:
			virtual void SetMouseCursorPosition(int x, int y) = 0;
			virtual void SetMouseInputMode(bool capture, bool hidden) = 0;
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