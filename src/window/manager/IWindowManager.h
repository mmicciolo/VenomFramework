#ifndef __IWINDOWMANAGER_
#define __IWINDOWMANAGER_

#include "../IWindow.h"
#include "../../input/keyboard/KeyboardState.h"
#include <functional>

namespace VF {
	namespace Window {
		class IWindowManager {
		public:
			virtual void AddWindow(IWindow * window) = 0;
			virtual void RemoveWindow(IWindow * window) = 0;
			virtual void PollForEvents() = 0;
			virtual void ShutDown() = 0;
			virtual IWindow * GetWindowByHandle(void * handlePtr) = 0;
			std::function<void(IWindow * window, VF::Input::KeyboardState state)> keyPressEvent;
			std::function<void(IWindow * window, VF::Input::MouseState mouseState)> mouseMoveEvent;
			std::function<void(IWindow * window, VF::Input::MouseState mouseState)> mouseButtonEvent;
			std::function<void(IWindow * window, VF::Input::MouseState mouseState)> mouseWheelEvent;
			std::function<void(IWindow * window)> moveEvent;
			std::function<void(IWindow * window)> resizeEvent;
			std::function<void(IWindow * window)> destroyedEvent;
		protected:
			std::vector<IWindow *> windows;
		private:
		};
	}
}


#endif