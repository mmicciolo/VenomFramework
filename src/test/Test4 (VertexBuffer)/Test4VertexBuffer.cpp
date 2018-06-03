#include "Test4VertexBuffer.h"
#include "../../graphics/buffer/VertexPosition/VertexPosition.h"
#include "../../graphics/buffer/VertexPositionColor/VertexPositionColor.h"

VF::Graphics::VertexBuffer * CreateVertexBuffer(VF::Graphics::IGraphicsDevice * graphicsDevice) {
	VF::Graphics::IVertexType ** vertices = new VF::Graphics::IVertexType*[3];
	//vertices[0] = new VF::Graphics::VertexPosition(*(new VF::Math::Vector3(-1.0f, -1.0f, 0.0f)));
	//vertices[1] = new VF::Graphics::VertexPosition(*(new VF::Math::Vector3(0.0f, 1.0f, 0.0f)));
	//vertices[2] = new VF::Graphics::VertexPosition(*(new VF::Math::Vector3(1.0f, -1.0f, 0.0f)));
	vertices[0] = new VF::Graphics::VertexPositionColor(*(new VF::Math::Vector3(-1.0f, -1.0f, 0.0f)), *(new VF::Math::Vector4(0.5f, 1.0f, 1.0f, 1.0f)));
	vertices[1] = new VF::Graphics::VertexPositionColor(*(new VF::Math::Vector3(0.0f, 1.0f, 0.0f)), *(new VF::Math::Vector4(1.0f, 0.5f, 1.0f, 1.0f)));
	vertices[2] = new VF::Graphics::VertexPositionColor(*(new VF::Math::Vector3(1.0f, -1.0f, 0.0f)), *(new VF::Math::Vector4(1.0f, 1.0f, 0.5f, 1.0f)));
	VF::Graphics::VertexBuffer * vertexBuffer = new VF::Graphics::VertexBuffer(graphicsDevice, 3, vertices[0]->GetVertexDecleration(), VF::Graphics::BufferUsage::Usage::WriteOnly);
	vertexBuffer->SetData(vertices);
	return vertexBuffer;
}

void Test4VertexBuffer::DrawTriangle() {
	//basicEffect.parameters.
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
	basicEffect = new VF::Graphics::BasicEffect(graphicsDevice);
	float ar = 640 / 480;
	basicEffect->parameters.projection = VF::Math::perspectiveFovLH<float>(VF::Math::radians(45.0f), 640.0f, 480.0f, 0.1f, 100.f);
	basicEffect->parameters.view = VF::Math::lookAtLH(VF::Math::Vector3(0, 0, -10), VF::Math::Vector3(0, 0, 0), VF::Math::Vector3(0, 1, 0));
	basicEffect->parameters.world = VF::Math::translate(VF::Math::Matrix4(1.0f), VF::Math::Vector3(0, 0, 0));
}

void Test4VertexBuffer::Update() {
	if (window->IsOpen()) {
		windowManager->PollForEvents();
		graphicsDevice->Clear();
		graphicsDevice->DrawPrimitives(vertexBuffer, basicEffect);
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