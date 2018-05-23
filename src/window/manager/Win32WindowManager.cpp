#include "Win32WindowManager.h"

#ifdef WINDOWS

void Win32WindowManager::AddWindow(IWindow * window) {
	if (window != nullptr) {
		windows.push_back(window);
		window->CreateNativeWindow(this);
	}
}

void Win32WindowManager::RemoveWindow(IWindow * window) {
	for (size_t i = 0; i < windows.size(); i++) {
		if (windows.at(i) == window) {
			windows.at(i)->Close();
		}
	}
}

void Win32WindowManager::PollForEvents() {
	MSG Msg;
	while (PeekMessage(&Msg, 0, 0, 0, PM_REMOVE))
	{
		TranslateMessage(&Msg);
		DispatchMessage(&Msg);
		if (Msg.message == WM_QUIT)
		{
			ShutDown();
		}
	}
}

void Win32WindowManager::ShutDown() {
	for (size_t i = 0; i < windows.size(); i++) {
		windows.at(i)->Close();
	}
}

IWindow * Win32WindowManager::GetWindowByHandle(long handlePtr) {
	for (size_t i = 0; i < windows.size(); i++) {
		if (windows.at(i)->GetWindowHandle() == handlePtr) {
			return windows.at(i);
		}
	}
	return nullptr;
}

#endif