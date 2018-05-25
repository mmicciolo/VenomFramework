#ifndef __TEST2_WINDOW_
#define __TEST2_WINDOW_

#include "../ITest.h"
#include "../../window/monitor/manager/MonitorManager.h"
#include "../../window/monitor/Monitor.h"
#include "../../window/manager/WindowManager.h"
#include "../../window/Window.h"
#include "../../input/keyboard/KeyboardState.h"
#include "../../input/mouse/MouseState.h"
#include <vector>

class Test2Input : public ITest {
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
	VF::Input::KeyboardState keyboardState;
	VF::Input::MouseState mouseState;
};

#endif