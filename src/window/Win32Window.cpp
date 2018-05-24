#include "Win32Window.h"
#include "monitor\manager\MonitorManager.h"
#include "manager\IWindowManager.h"
#include "../input/Keyboard/Keyboard.h"
#include "../input/Keyboard/Keys.h"
#include "../input/mouse/Mouse.h"
#include "../input/mouse/MouseState.h"

#ifdef WINDOWS

VF::Window::Win32Window::Win32Window() {

}

VF::Window::Win32Window::Win32Window(int width, int height) {
	this->width = width;
	this->height = height;
	this->title = " ";
	MonitorManager monitorManager;
	this->monitor = *monitorManager.GetPrimaryMonitor();
	this->x = this->monitor.GetPosition()->x;
	this->y = this->monitor.GetPosition()->y;
}

VF::Window::Win32Window::Win32Window(int width, int height, std::string title) {
	this->width = width;
	this->height = height;
	this->title = title;
	MonitorManager monitorManager;
	this->monitor = *monitorManager.GetPrimaryMonitor();
	this->x = this->monitor.GetPosition()->x;
	this->y = this->monitor.GetPosition()->y;
}

VF::Window::Win32Window::Win32Window(int width, int height, std::string title, Monitor * monitor) {
	this->width = width;
	this->height = height;
	this->title = title;
	this->monitor = *monitor;
	this->x = this->monitor.GetPosition()->x;
	this->y = this->monitor.GetPosition()->y;
}

VF::Window::Win32Window::~Win32Window() {

}

long VF::Window::Win32Window::GetWindowHandle() {
	return (long)hwnd;
}

VF::Input::Keys::Key TranslateExtended(WPARAM wParam, LPARAM lParam) {

	VF::Input::Keys::Key key = (VF::Input::Keys::Key) wParam;
	int extended = (lParam >> 24) & 0x01;
	switch (key) {
	case
	VF::Input::Keys::Key::Control: {
		return extended ? VF::Input::Keys::Key::RightControl : VF::Input::Keys::Key::LeftControl;
	}
	case VF::Input::Keys::Key::Shift:
		return extended ? VF::Input::Keys::Key::RightShift : VF::Input::Keys::Key::LeftShift;
	case VF::Input::Keys::Key::Menu:
		return extended ? VF::Input::Keys::Key::RightAlt : VF::Input::Keys::Key::LeftAlt;
	}
	return key;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	VF::Window::IWindowManager * windowManager = (VF::Window::IWindowManager *)GetWindowLongPtr(hwnd, GWLP_USERDATA);
	VF::Window::IWindow * window = nullptr;
	if (windowManager != nullptr) {
		window = windowManager->GetWindowByHandle((long)hwnd);
	}

	switch (msg)
	{
	case WM_CLOSE: {
		window->SetOpen(false);
		if (windowManager->destroyedEvent != nullptr) {
			windowManager->destroyedEvent(window);
		}
		break;
	}
	case WM_CHAR:
	case WM_SYSCHAR:
	case WM_UNICHAR: {
		break;
	}
	case WM_KEYDOWN:
	case WM_KEYUP:
	case WM_SYSKEYDOWN:
	case WM_SYSKEYUP: {
		VF::Input::KeyState::State state = ((lParam >> 31) & 1) ? VF::Input::KeyState::State::Up : VF::Input::KeyState::State::Down;
		VF::Input::Keys::Key wParamKey = (VF::Input::Keys::Key) wParam;
		VF::Input::Keys::Key translatedKey = TranslateExtended(wParam, lParam);
		VF::Input::KeyState::State * keyState = (VF::Input::KeyState::State *) GetProp(hwnd, "KEYSTATE");
		keyState[wParamKey] = state;
		keyState[translatedKey] = state;
		if (windowManager->keyPressEvent != nullptr) {
			VF::Input::KeyboardState keyboardState;
			VF::Input::Keyboard::GetState(windowManager->GetWindowByHandle((long)hwnd), keyboardState);
			windowManager->keyPressEvent(window, keyboardState);
		}
		break;
	}
	case WM_MOUSEMOVE: {
		VF::Input::MouseData * mouseData = (VF::Input::MouseData *) GetProp(hwnd, "MOUSEDATA");
		mouseData->position.x = (int)LOWORD(lParam);
		mouseData->position.y = (int)HIWORD(lParam);
		if (windowManager->mouseMoveEvent != nullptr) {
			VF::Input::MouseState mouseState;
			VF::Input::Mouse::GetState(windowManager->GetWindowByHandle((long)hwnd), mouseState);
			windowManager->mouseMoveEvent(window, mouseState);
		}
		break;
	}
	case WM_LBUTTONDOWN:
	case WM_RBUTTONDOWN:
	case WM_MBUTTONDOWN:
	case WM_XBUTTONDOWN:
	case WM_LBUTTONUP:
	case WM_RBUTTONUP:
	case WM_MBUTTONUP:
	case WM_XBUTTONUP: {
		VF::Input::MouseData * mouseData = (VF::Input::MouseData *) GetProp(hwnd, "MOUSEDATA");
		VF::Input::ButtonState::State buttonState;
		if (msg == WM_LBUTTONDOWN || msg == WM_RBUTTONDOWN || msg == WM_MBUTTONDOWN || msg == WM_XBUTTONDOWN) { buttonState = VF::Input::ButtonState::State::Pressed; }
		else { buttonState = VF::Input::ButtonState::State::Released;}
		if (msg == WM_LBUTTONDOWN || msg == WM_LBUTTONUP) { mouseData->leftButton = buttonState; }
		if (msg == WM_RBUTTONDOWN || msg == WM_RBUTTONUP) { mouseData->rightButton = buttonState; }
		if (msg == WM_MBUTTONDOWN || msg == WM_MBUTTONUP) { mouseData->middleButton = buttonState; }
		if (GET_XBUTTON_WPARAM(wParam) == XBUTTON1) { mouseData->XButton1 = buttonState; }
		if (GET_XBUTTON_WPARAM(wParam) == XBUTTON2) { mouseData->XButton2 = buttonState; }
		if (windowManager->mouseButtonEvent != nullptr) {
			VF::Input::MouseState mouseState;
			VF::Input::Mouse::GetState(windowManager->GetWindowByHandle((long)hwnd), mouseState);
			windowManager->mouseButtonEvent(window, mouseState);
		}
		break;
	}
	case WM_MOUSEWHEEL: {
		VF::Input::MouseData * mouseData = (VF::Input::MouseData *) GetProp(hwnd, "MOUSEDATA");
		mouseData->scrollWheelValue = (int)((SHORT)HIWORD(wParam) / (double) WHEEL_DELTA);
		if (windowManager->mouseWheelEvent != nullptr) {
			VF::Input::MouseState mouseState;
			VF::Input::Mouse::GetState(windowManager->GetWindowByHandle((long)hwnd), mouseState);
			windowManager->mouseWheelEvent(window, mouseState);
		}
		break;
	}
	case WM_MOUSEHWHEEL: {
		VF::Input::MouseData * mouseData = (VF::Input::MouseData *) GetProp(hwnd, "MOUSEDATA");
		mouseData->scrollWheelValue = (int)-((SHORT)HIWORD(wParam) / (double)WHEEL_DELTA);
		if (windowManager->mouseWheelEvent != nullptr) {
			VF::Input::MouseState mouseState;
			VF::Input::Mouse::GetState(windowManager->GetWindowByHandle((long)hwnd), mouseState);
			windowManager->mouseWheelEvent(window, mouseState);
		}
		break;
	}
	default:
		return DefWindowProc(hwnd, msg, wParam, lParam);
	}
	return 0;
}

void VF::Window::Win32Window::CreateNativeWindow(IWindowManager * windowManager) {

	hInstance = GetModuleHandle(0);

	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = 0;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wc.lpszMenuName = title.c_str();
	wc.lpszClassName = title.c_str();
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	RegisterClassEx(&wc);

	hwnd = CreateWindowEx(
		WS_EX_CLIENTEDGE,
		title.c_str(),
		title.c_str(),
		WS_OVERLAPPEDWINDOW,
		monitor.GetPosition()->x, monitor.GetPosition()->y, width, height,
		NULL, NULL, GetModuleHandleW(NULL), NULL);

	SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)windowManager);
	SetProp(hwnd, "KEYSTATE", this->keyState);
	SetProp(hwnd, "MOUSEDATA", &this->mouseData);

	ShowWindow(hwnd, 1);
	UpdateWindow(hwnd);

	open = true;
}

void VF::Window::Win32Window::SetWindowTitle(std::string title) {
	SetWindowText(hwnd, title.c_str());
}

void VF::Window::Win32Window::SetWindowIcon() {

}

void VF::Window::Win32Window::SetWindowPosition(int x, int y) {
	SetWindowPos(hwnd, NULL, x, y, width, height, 0);
}

void VF::Window::Win32Window::SetWindowSize(int width, int height) {
	this->width = width;
	this->height = height;
	SetWindowPos(hwnd, NULL, x, y, width, height, 0);
}

void VF::Window::Win32Window::HideWindow(bool hide) {
	if (hide) {
		ShowWindow(hwnd, SW_HIDE);
	}
	else {
		ShowWindow(hwnd, SW_SHOWNORMAL);
	}
}

void VF::Window::Win32Window::EnableFullscreen() {

}

void VF::Window::Win32Window::DisableFullscreen() {

}

void VF::Window::Win32Window::Close() {
	open = false;
	DestroyWindow(hwnd);
	UnregisterClass(title.c_str(), hInstance);
}

#endif