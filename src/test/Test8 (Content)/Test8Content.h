#ifndef __TEST8_CONTENT_
#define __TEST8_CONTENT_

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
#include "../../graphics/texture/Texture2D.h"
#include "../../graphics/animation/Animator.h"
#include <vector>

namespace VF {
	namespace Graphics {
		class Model;
	}
}

class Test8Content : public ITest {
public:
	void Init();
	void Update();
	void Shutdown();
	void SetupCamera();
	void UpdateCamera();
	void Draw();
	void LoadModel();
protected:
private:
	VF::Window::IMonitorManager * monitorManager;
	VF::Window::Monitor * monitor;
	std::vector<VF::Window::Monitor *> monitors;
	VF::Window::IWindowManager * windowManager;
	VF::Window::Window * window;
	VF::Graphics::GraphicsDevice * graphicsDevice;
	VF::Camera::FirstPersonCamera * camera;
	VF::Input::KeyboardState keyboardState;
	VF::Input::MouseState mouseState;
	VF::Graphics::Model * model;
	VF::Graphics::Texture2D * texture2D;
	VF::Graphics::Animator * animator;
	int keyCount = 0;
};

#endif