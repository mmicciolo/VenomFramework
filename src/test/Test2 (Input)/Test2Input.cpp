#include "Test2Input.h"
#include "../../input/keyboard/Keyboard.h"
#include "../../input/mouse/Mouse.h"

#include <iostream>


void Test2Input::Init() {
	monitorManager = new VF::Window::MonitorManager();
	monitor = monitorManager->GetPrimaryMonitor();
	monitors = monitorManager->GetMonitors();
	windowManager = new VF::Window::WindowManager();
	window = new VF::Window::Window(640, 480, "Test 1 Window");
	windowManager->AddWindow(window);
}

void Test2Input::Update() {
	if (window->IsOpen()) {

		windowManager->PollForEvents();

		VF::Input::Keyboard::GetState(window, keyboardState);
		if (keyboardState.IsKeyDown(VF::Input::Keys::Key::A) || keyboardState.IsKeyDown(VF::Input::Keys::Key::Space)) {
			std::cout << "Key A is down!" << std::endl;
		}

		VF::Input::Mouse::GetState(window, mouseState);
		if (mouseState.IsButtonPressed(VF::Input::MouseButtons::Buttons::LEFT_BUTTON)) {
			std::cout << "Left Mouse Button Pressed!" << std::endl;
		}
	}
	else {
		running = false;
	}
}

void Test2Input::Shutdown() {
	windowManager->ShutDown();
}