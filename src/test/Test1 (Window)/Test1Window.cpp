#include "Test1Window.h"

void Test1Window::Init() {
	monitorManager = new VF::Window::MonitorManager();
	monitor = monitorManager->GetPrimaryMonitor();
	monitors = monitorManager->GetMonitors();
	windowManager = new VF::Window::WindowManager();
	window = new VF::Window::Window(640, 480, "Test 1 Window");
	windowManager->AddWindow(window);
}

void Test1Window::Update() {
	if (window->IsOpen()) {
		windowManager->PollForEvents();
	}
	else {
		running = false;
	}
}

void Test1Window::Shutdown() {
	windowManager->ShutDown();
}