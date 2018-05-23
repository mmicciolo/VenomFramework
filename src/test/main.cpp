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

void HandleWindowDestroy(IWindow * window) {
	int i = 0;
}

int main() {

	IMonitorManager * monitorManager = new MonitorManager();

	Monitor * monitor = monitorManager->GetPrimaryMonitor();

	std::vector<Monitor *> monitors = monitorManager->GetMonitors();

	IWindowManager * windowManager = new WindowManager();
	Window * window = new Window(640, 480);
	windowManager->AddWindow(window);
	windowManager->destroyedEvent = HandleWindowDestroy;

	while (window->IsOpen()) {
		windowManager->PollForEvents();
		KeyboardState state;
		Keyboard::GetState(window, state);
		if (state.IsKeyDown(Keys::Key::A) || state.IsKeyDown(Keys::Key::Space)) {
			std::cout << "Key A is down!";
		}
	}

	windowManager->ShutDown();

	return 0;
}