#ifndef __WIN32_WINDOW_
#define __WIN32_WINDOW_

#include "IWindow.h"
#include "../platform/platform.h"

#ifdef WINDOWS
#include <Windows.h>

namespace VF {
	namespace Window {
		class Win32Window : public IWindow {
		public:
			Win32Window();
			Win32Window(int width, int height);
			Win32Window(int width, int height, std::string title);
			Win32Window(int width, int height, std::string title, Monitor * monitor);
			~Win32Window();
			void SetWindowTitle(std::string title);
			void SetWindowIcon();
			void SetWindowPosition(int x, int y);
			void SetWindowSize(int width, int height);
			void HideWindow(bool hide);
			void EnableFullscreen();
			void DisableFullscreen();
			void CreateNativeWindow(IWindowManager * windowManager);
			void Close();
			long GetWindowHandle();
		protected:
			void SetMouseCursorPosition(int x, int y);
			void SetMouseInputMode(bool capture, bool hidden);
		private:
			HDC	hdc;
			WNDCLASSEX wc;
			HWND hwnd;
			HINSTANCE hInstance;
		};
	}
}

#endif

#endif