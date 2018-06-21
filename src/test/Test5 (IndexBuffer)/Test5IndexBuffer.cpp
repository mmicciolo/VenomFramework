#include "Test5IndexBuffer.h"
#include "../../graphics/buffer/VertexDeclaration.h"

void Test5IndexBuffer::CreateVertexBuffer() {
	VF::Graphics::VertexDeclaration ** vertices = new VF::Graphics::VertexDeclaration*[4];
	vertices[0] = (new VF::Graphics::VertexDeclaration())->begin()->addVertexElement(new VF::Graphics::PositionVertexElement(VF::Math::Vector3(1.0f, 1.0f, 0.0f)))
		->addVertexElement(new VF::Graphics::ColorVertexElement(VF::Math::Vector4(1.0f, 1.0f, 0.5f, 1.0f)))->end();
	vertices[1] = (new VF::Graphics::VertexDeclaration())->begin()->addVertexElement(new VF::Graphics::PositionVertexElement(VF::Math::Vector3(-1.0f, 1.0f, 0.0f)))
		->addVertexElement(new VF::Graphics::ColorVertexElement(VF::Math::Vector4(1.0f, 0.5f, 1.0f, 1.0f)))->end();
	vertices[2] = (new VF::Graphics::VertexDeclaration())->begin()->addVertexElement(new VF::Graphics::PositionVertexElement(VF::Math::Vector3(-1.0f, -1.0f, 0.0f)))
		->addVertexElement(new VF::Graphics::ColorVertexElement(VF::Math::Vector4(0.5f, 1.0f, 1.0f, 1.0f)))->end();
	vertices[3] = (new VF::Graphics::VertexDeclaration())->begin()->addVertexElement(new VF::Graphics::PositionVertexElement(VF::Math::Vector3(1.0f, -1.0f, 0.0f)))
		->addVertexElement(new VF::Graphics::ColorVertexElement(VF::Math::Vector4(1.0f, 0.5f, 1.0f, 1.0f)))->end();
	vertexBuffer = new VF::Graphics::VertexBuffer(graphicsDevice, 4);
	vertexBuffer->SetData(vertices);
}

void Test5IndexBuffer::CreateIndexBuffer() {
	static unsigned int indices[6] = { 0, 1, 2,
								2, 3, 0};
	indexBuffer = new VF::Graphics::IndexBuffer(graphicsDevice, 6);
	indexBuffer->SetData(indices);
}

void Test5IndexBuffer::Init() {
	monitorManager = new VF::Window::MonitorManager();
	monitor = monitorManager->GetPrimaryMonitor();
	monitors = monitorManager->GetMonitors();
	windowManager = new VF::Window::WindowManager();
	window = new VF::Window::Window(640, 480, "Test 5 Index Buffer");
	windowManager->AddWindow(window);
	VF::Graphics::Viewport viewPort;
	graphicsDevice = new VF::Graphics::GraphicsDevice(window, viewPort);
	graphicsDevice->Init();
	CreateVertexBuffer();
	CreateIndexBuffer();
	basicEffect = new VF::Graphics::BasicEffect();
	float ar = 640 / 480;
	basicEffect->projectionViewWorld.projection = VF::Math::perspectiveFovLH<float>(VF::Math::radians(45.0f), 640.0f, 480.0f, 0.1f, 100.f);
	basicEffect->projectionViewWorld.view = VF::Math::lookAtLH(VF::Math::Vector3(0, 0, -10), VF::Math::Vector3(0, 0, 0), VF::Math::Vector3(0, 1, 0));
	basicEffect->projectionViewWorld.world = VF::Math::translate(VF::Math::Matrix4(1.0f), VF::Math::Vector3(0, 0, 0));
}

void Test5IndexBuffer::Update() {
	if (window->IsOpen()) {
		windowManager->PollForEvents();
		graphicsDevice->Clear();
		graphicsDevice->DrawIndexedPrimitives(vertexBuffer, indexBuffer, basicEffect);
		//graphicsDevice->DrawPrimitives(vertexBuffer, basicEffect);
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