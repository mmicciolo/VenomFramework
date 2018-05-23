#include "../window/monitor/Monitor.h"
#include "../window/monitor/manager/MonitorManager.h"
#include "../window/Window.h"
#include "../window/manager/WindowManager.h"

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
	}

	windowManager->ShutDown();

	return 0;
}