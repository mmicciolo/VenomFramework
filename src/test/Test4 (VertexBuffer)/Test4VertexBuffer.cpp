#include "Test4VertexBuffer.h"
#include "../../graphics/buffer/VertexPosition/VertexPosition.h"

VF::Graphics::VertexBuffer * CreateVertexBuffer(VF::Graphics::IGraphicsDevice * graphicsDevice) {
	VF::Graphics::IVertexType ** vertices = new VF::Graphics::IVertexType*[3];
	vertices[0] = new VF::Graphics::VertexPosition(*(new VF::Math::Vector3(-1.0f, -1.0f, 0.0f)));
	vertices[1] = new VF::Graphics::VertexPosition(*(new VF::Math::Vector3(0.0f, 1.0f, 0.0f)));
	vertices[2] = new VF::Graphics::VertexPosition(*(new VF::Math::Vector3(1.0f, -1.0f, 0.0f)));
	VF::Graphics::VertexBuffer * vertexBuffer = new VF::Graphics::VertexBuffer(graphicsDevice, 3, vertices[0]->GetVertexDecleration(), VF::Graphics::BufferUsage::Usage::WriteOnly);
	vertexBuffer->SetData(vertices);
	return vertexBuffer;
	//vertexBuffer->SetData<VF::Graphics::VertexPosition>(vertices);
}

void Test4VertexBuffer::Init() {
	monitorManager = new VF::Window::MonitorManager();
	monitor = monitorManager->GetPrimaryMonitor();
	monitors = monitorManager->GetMonitors();
	windowManager = new VF::Window::WindowManager();
	window = new VF::Window::Window(640, 480, "Test 4 Vertex Buffer");
	windowManager->AddWindow(window);
	graphicsDevice = new VF::Graphics::GraphicsDevice(window);
	graphicsDevice->Init();
	vertexBuffer = CreateVertexBuffer(graphicsDevice);
}

void Test4VertexBuffer::Update() {
	if (window->IsOpen()) {
		windowManager->PollForEvents();
		graphicsDevice->Clear();
		graphicsDevice->DrawPrimitives(vertexBuffer);
		graphicsDevice->Present();
	}
	else {
		running = false;
	}
}

void Test4VertexBuffer::Shutdown() {
	graphicsDevice->Shutdown();
	windowManager->ShutDown();
}