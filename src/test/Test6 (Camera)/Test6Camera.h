#ifndef __TEST6_CAMERA_
#define __TEST6_CAMERA_

#include "../ITest.h"
#include "../../window/monitor/manager/MonitorManager.h"
#include "../../window/monitor/Monitor.h"
#include "../../window/manager/WindowManager.h"
#include "../../window/Window.h"
#include "../../graphics/device/GraphicsDevice.h"
#include "../../graphics/buffer/VertexBuffer.h"
#include "../../graphics/effect/basiceffect/BasicEffect.h"
#include "../../camera/FirstPersonCamera.h"
#include "../../input/keyboard/KeyboardState.h"
#include "../../input/mouse/MouseState.h"
#include "../../input/mouse/Mouse.h"
#include <vector>

class Test6Camera : public ITest {
public:
	void Init();
	void Update();
	void Shutdown();
	void SetupCamera();
	void UpdateCamera();
	void Draw();
protected:
private:
	VF::Window::IMonitorManager * monitorManager;
	VF::Window::Monitor * monitor;
	std::vector<VF::Window::Monitor *> monitors;
	VF::Window::IWindowManager * windowManager;
	VF::Window::Window * window;
	VF::Graphics::GraphicsDevice * graphicsDevice;
	VF::Graphics::VertexBuffer * vertexBuffer;
	VF::Graphics::BasicEffect * basicEffect;
	VF::Camera::FirstPersonCamera * camera;
	VF::Input::KeyboardState keyboardState;
	VF::Input::MouseState mouseState;
};

#endif