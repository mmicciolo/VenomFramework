#include "../window/monitor/Monitor.h"
#include "../window/monitor/manager/MonitorManager.h"
#include "../window/Window.h"
#include "../window/manager/WindowManager.h"
#include "../input/Keyboard.h"
#include "../input/KeyboardState.h"
#include "../input/Keys.h"
#include "../input/KeyState.h"

#include <iostream>
#include <vector>

void HandleWindowDestroy(VF::Window::IWindow * window) {
	int i = 0;
}

int main() {

	VF::Window::IMonitorManager * monitorManager = new MonitorManager();

	VF::Window::Monitor * monitor = monitorManager->GetPrimaryMonitor();

	std::vector<VF::Window::Monitor *> monitors = monitorManager->GetMonitors();

	VF::Window::IWindowManager * windowManager = new WindowManager();
	Window * window = new Window(640, 480);
	windowManager->AddWindow(window);
	windowManager->destroyedEvent = HandleWindowDestroy;

	while (window->IsOpen()) {
		windowManager->PollForEvents();
		VF::Input::KeyboardState state;
		VF::Input::Keyboard::GetState(window, state);
		if (state.IsKeyDown(VF::Input::Keys::Key::A) || state.IsKeyDown(VF::Input::Keys::Key::Space)) {
			std::cout << "Key A is down!";
		}
	}

	windowManager->ShutDown();

	return 0;
}