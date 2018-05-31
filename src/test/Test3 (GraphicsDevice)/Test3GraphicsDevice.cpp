#include "Test3GraphicsDevice.h"

void Test3GraphicsDevice::Init() {
	monitorManager = new VF::Window::MonitorManager();
	monitor = monitorManager->GetPrimaryMonitor();
	monitors = monitorManager->GetMonitors();
	windowManager = new VF::Window::WindowManager();
	window = new VF::Window::Window(640, 480, "Test 3 Graphics Device");
	windowManager->AddWindow(window);
	graphicsDevice = new VF::Graphics::GraphicsDevice(window);
	graphicsDevice->Init();
}

void Test3GraphicsDevice::Update() {
	if (window->IsOpen()) {
		windowManager->PollForEvents();
		graphicsDevice->Clear();
		graphicsDevice->Present();
	}
	else {
		running = false;
	}
}

void Test3GraphicsDevice::Shutdown() {
	graphicsDevice->Shutdown();
	windowManager->ShutDown();
}