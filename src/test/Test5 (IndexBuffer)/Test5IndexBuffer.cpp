#include "Test5IndexBuffer.h"
#include "../../graphics/buffer/VertexPosition/VertexPosition.h"
#include "../../graphics/buffer/VertexPositionColor/VertexPositionColor.h"
void Test5IndexBuffer::CreateVertexBuffer() {
	VF::Graphics::IVertexType ** vertices = new VF::Graphics::IVertexType*[4];
	vertices[0] = new VF::Graphics::VertexPositionColor(*(new VF::Math::Vector3(-1.0f, -1.0f, 0.0f)), *(new VF::Math::Vector4(0.5f, 1.0f, 1.0f, 1.0f)));
	vertices[1] = new VF::Graphics::VertexPositionColor(*(new VF::Math::Vector3(-1.0f, 1.0f, 0.0f)), *(new VF::Math::Vector4(1.0f, 0.5f, 1.0f, 1.0f)));
	vertices[2] = new VF::Graphics::VertexPositionColor(*(new VF::Math::Vector3(1.0f, 1.0f, 0.0f)), *(new VF::Math::Vector4(1.0f, 1.0f, 0.5f, 1.0f)));
	vertices[3] = new VF::Graphics::VertexPositionColor(*(new VF::Math::Vector3(1.0f, -1.0f, 0.0f)), *(new VF::Math::Vector4(1.0f, 0.5f, 1.0f, 1.0f)));
	vertexBuffer = new VF::Graphics::VertexBuffer(graphicsDevice, 4, vertices[0]->GetVertexDecleration(), VF::Graphics::BufferUsage::Usage::WriteOnly);
	vertexBuffer->SetData(vertices);
}

void Test5IndexBuffer::CreateIndexBuffer() {
	unsigned int indices[6] = { 0, 1, 2,
								3, 0, 2};
	indexBuffer = new VF::Graphics::IndexBuffer(graphicsDevice, 6, VF::Graphics::BufferUsage::WriteOnly);
	indexBuffer->SetData(indices);
}

void Test5IndexBuffer::Init() {
	monitorManager = new VF::Window::MonitorManager();
	monitor = monitorManager->GetPrimaryMonitor();
	monitors = monitorManager->GetMonitors();
	windowManager = new VF::Window::WindowManager();
	window = new VF::Window::Window(640, 480, "Test 5 Index Buffer");
	windowManager->AddWindow(window);
	graphicsDevice = new VF::Graphics::GraphicsDevice(window);
	graphicsDevice->Init();
	CreateVertexBuffer();
	CreateIndexBuffer();
	basicEffect = new VF::Graphics::BasicEffect(graphicsDevice);
	float ar = 640 / 480;
	basicEffect->parameters.projection = VF::Math::perspectiveFovLH<float>(VF::Math::radians(45.0f), 640.0f, 480.0f, 0.1f, 100.f);
	basicEffect->parameters.view = VF::Math::lookAtLH(VF::Math::Vector3(0, 0, -10), VF::Math::Vector3(0, 0, 0), VF::Math::Vector3(0, 1, 0));
	basicEffect->parameters.world = VF::Math::translate(VF::Math::Matrix4(1.0f), VF::Math::Vector3(0, 0, 0));
}

void Test5IndexBuffer::Update() {
	if (window->IsOpen()) {
		windowManager->PollForEvents();
		graphicsDevice->Clear();
		graphicsDevice->DrawIndexedPrimitives(vertexBuffer, indexBuffer, basicEffect);
		graphicsDevice->Present();
	}
	else {
		running = false;
	}
}

void Test5IndexBuffer::Shutdown() {
	graphicsDevice->Shutdown();
	windowManager->ShutDown();
}