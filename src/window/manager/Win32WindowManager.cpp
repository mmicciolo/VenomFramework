#include "Win32WindowManager.h"

#ifdef WINDOWS

void VF::Window::Win32WindowManager::AddWindow(IWindow * window) {
	if (window != nullptr) {
		windows.push_back(window);
		window->CreateNativeWindow(this);
	}
}

void VF::Window::Win32WindowManager::RemoveWindow(IWindow * window) {
	for (size_t i = 0; i < windows.size(); i++) {
		if (windows.at(i) == window) {
			windows.at(i)->Close();
		}
	}
}

void VF::Window::Win32WindowManager::PollForEvents() {
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

void VF::Window::Win32WindowManager::ShutDown() {
	for (size_t i = 0; i < windows.size(); i++) {
		windows.at(i)->Close();
	}
}

VF::Window::IWindow * VF::Window::Win32WindowManager::GetWindowByHandle(long handlePtr) {
	for (size_t i = 0; i < windows.size(); i++) {
		if (windows.at(i)->GetWindowHandle() == handlePtr) {
			return windows.at(i);
		}
	}
	return nullptr;
}

#endif