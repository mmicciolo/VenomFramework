#ifndef __TEST3_GRAPHICS_DEVICE_
#define __TEST3_GRAPHICS_DEVICE_

#include "../ITest.h"
#include "../../window/monitor/manager/MonitorManager.h"
#include "../../window/monitor/Monitor.h"
#include "../../window/manager/WindowManager.h"
#include "../../window/Window.h"
#include "../../graphics/device/GraphicsDevice.h"
#include <vector>

class Test3GraphicsDevice : public ITest {
public:
	void Init();
	void Update();
	void Shutdown();
protected:
private:
	VF::Window::IMonitorManager * monitorManager;
	VF::Window::Monitor * monitor;
	std::vector<VF::Window::Monitor *> monitors;
	VF::Window::IWindowManager * windowManager;
	VF::Window::Window * window;
	VF::Graphics::GraphicsDevice * graphicsDevice;
};

#endif