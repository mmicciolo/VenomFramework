#include "Win32Window.h"
#include "monitor\manager\MonitorManager.h"
#include "manager\IWindowManager.h"
#include "../input/Keyboard.h"
#include "../input/Keys.h"

#ifdef WINDOWS

Win32Window::Win32Window() {

}

Win32Window::Win32Window(int width, int height) {
	this->width = width;
	this->height = height;
	this->title = " ";
	MonitorManager monitorManager;
	this->monitor = *monitorManager.GetPrimaryMonitor();
}

Win32Window::Win32Window(int width, int height, std::string title) {
	this->width = width;
	this->height = height;
	this->title = title;
	MonitorManager monitorManager;
	this->monitor = *monitorManager.GetPrimaryMonitor();
}

Win32Window::Win32Window(int width, int height, std::string title, Monitor * monitor) {
	this->width = width;
	this->height = height;
	this->title = title;
	this->monitor = *monitor;
}

Win32Window::~Win32Window() {

}

long Win32Window::GetWindowHandle() {
	return (long)hwnd;
}

Keys::Key TranslateExtended(WPARAM wParam, LPARAM lParam) {
	Keys::Key key = (Keys::Key) wParam;
	int extended = (lParam >> 24) & 0x01;
	switch (key) {
	case Keys::Key::Control: {
		return extended ? Keys::Key::RightControl : Keys::Key::LeftControl;
	}
	case Keys::Key::Shift:
		return extended ? Keys::Key::RightShift : Keys::Key::LeftShift;
	case Keys::Key::Menu:
		return extended ? Keys::Key::RightAlt : Keys::Key::LeftAlt;
	}
	return key;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	IWindowManager * windowManager = (IWindowManager *)GetWindowLongPtr(hwnd, GWLP_USERDATA);
	IWindow * window = nullptr;
	if (windowManager != nullptr) {
		window = windowManager->GetWindowByHandle((long)hwnd);
	}

	switch (msg)
	{
	case WM_CLOSE:
		window->SetOpen(false);
		if (windowManager->destroyedEvent != nullptr) {
			windowManager->destroyedEvent(window);
		}
		break;
	case WM_KEYDOWN:
	case WM_KEYUP:
	case WM_SYSKEYDOWN:
	case WM_SYSKEYUP: {
		KeyState::State state = ((lParam >> 31) & 1) ? KeyState::State::Up : KeyState::State::Down;
		Keys::Key wParamKey = (Keys::Key) wParam;
		Keys::Key translatedKey = TranslateExtended(wParam, lParam);
		KeyState::State * keyState = (KeyState::State *) GetProp(hwnd, "KEYSTATE");
		keyState[wParamKey] = state;
		keyState[translatedKey] = state;
		break;
	}
	default:
		return DefWindowProc(hwnd, msg, wParam, lParam);
	}
	return 0;
}

void Win32Window::CreateNativeWindow(IWindowManager * windowManager) {

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

	ShowWindow(hwnd, 1);
	UpdateWindow(hwnd);

	open = true;
}

void Win32Window::Close() {
	open = false;
	DestroyWindow(hwnd);
	UnregisterClass(title.c_str(), hInstance);
}

#endif