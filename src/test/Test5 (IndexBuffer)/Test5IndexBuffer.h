#ifndef __TEST4_INDEX_BUFFER_
#define __TEST4_INDEX_BUFFER_

#include "../ITest.h"
#include "../../window/monitor/manager/MonitorManager.h"
#include "../../window/monitor/Monitor.h"
#include "../../window/manager/WindowManager.h"
#include "../../window/Window.h"
#include "../../graphics/device/GraphicsDevice.h"
#include "../../graphics/buffer/VertexBuffer.h"
#include "../../graphics/buffer/IndexBuffer.h"
#include "../../graphics/effect/basiceffect/BasicEffect.h"
#include <vector>

class Test5IndexBuffer : public ITest {
public:
	void Init();
	void Update();
	void Shutdown();
	void CreateVertexBuffer();
	void CreateIndexBuffer();
protected:
private:
	VF::Window::IMonitorManager * monitorManager;
	VF::Window::Monitor * monitor;
	std::vector<VF::Window::Monitor *> monitors;
	VF::Window::IWindowManager * windowManager;
	VF::Window::Window * window;
	VF::Graphics::GraphicsDevice * graphicsDevice;
	VF::Graphics::VertexBuffer * vertexBuffer;
	VF::Graphics::IndexBuffer * indexBuffer;
	VF::Graphics::BasicEffect * basicEffect;
};

#endif