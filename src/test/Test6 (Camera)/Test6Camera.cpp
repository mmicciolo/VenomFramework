#include "Test6Camera.h"
#include "../../graphics/buffer/VertexPosition/VertexPosition.h"
#include "../../graphics/buffer/VertexPositionColor/VertexPositionColor.h"

VF::Graphics::VertexBuffer * CreateVertexBuffer2(VF::Graphics::GraphicsDevice * graphicsDevice) {
	VF::Graphics::VertexDeclaration ** vertices = new VF::Graphics::VertexDeclaration*[6];
	vertices[0] = new VF::Graphics::VertexPositionColor(*(new VF::Math::Vector3(200.0f, 200.0f, 0.0f)), *(new VF::Math::Vector4(0.5f, 1.0f, 1.0f, 1.0f)));
	vertices[1] = new VF::Graphics::VertexPositionColor(*(new VF::Math::Vector3(-200.0f, 200.0f, 0.0f)), *(new VF::Math::Vector4(1.0f, 0.5f, 1.0f, 1.0f)));
	vertices[2] = new VF::Graphics::VertexPositionColor(*(new VF::Math::Vector3(-200.0f, -200.0f, 0.0f)), *(new VF::Math::Vector4(1.0f, 1.0f, 0.5f, 1.0f)));
	vertices[3] = new VF::Graphics::VertexPositionColor(*(new VF::Math::Vector3(200.0f, 200.0f, 0.0f)), *(new VF::Math::Vector4(1.0f, 0.5f, 1.0f, 1.0f)));
	vertices[4] = new VF::Graphics::VertexPositionColor(*(new VF::Math::Vector3(-200.0f, -200.0f, 0.0f)), *(new VF::Math::Vector4(1.0f, 0.5f, 1.0f, 1.0f)));
	vertices[5] = new VF::Graphics::VertexPositionColor(*(new VF::Math::Vector3(200.0f, -200.0f, 0.0f)), *(new VF::Math::Vector4(1.0f, 1.0f, 0.5f, 1.0f)));
	VF::Graphics::VertexBuffer * vertexBuffer = new VF::Graphics::VertexBuffer(graphicsDevice, 6, new VF::Graphics::VertexPositionColor());
	vertexBuffer->SetData(vertices);
	return vertexBuffer;
}

void Test6Camera::SetupCamera() {
	VF::Camera::PerspectiveProjectionParameters parameters;
	parameters.fieldOfView = 45.0f;
	parameters.width = 640;
	parameters.height = 480;
	parameters.nearClip = 0.1f;
	parameters.farClip = 1000.0f;
	camera = new VF::Camera::FirstPersonCamera(parameters, VF::Math::Vector3(0, 25, -50), VF::Math::Vector3(0, 0, 0));
	VF::Input::Mouse::SetMouseInputMode(window, true, false);
}

void Test6Camera::Init() {
	monitorManager = new VF::Window::MonitorManager();
	monitor = monitorManager->GetPrimaryMonitor();
	monitors = monitorManager->GetMonitors();
	windowManager = new VF::Window::WindowManager();
	window = new VF::Window::Window(640, 480, "Test 6 Camera");
	windowManager->AddWindow(window);
	VF::Graphics::Viewport viewPort;
	graphicsDevice = new VF::Graphics::GraphicsDevice(window, viewPort);
	graphicsDevice->Init();
	vertexBuffer = CreateVertexBuffer2(graphicsDevice);
	SetupCamera();
	basicEffect = new VF::Graphics::BasicEffect();
}

void Test6Camera::Update() {
	if (window->IsOpen()) {
		windowManager->PollForEvents();
		graphicsDevice->Clear();
		UpdateCamera();
		Draw();
		graphicsDevice->Present();
	}
	else {
		running = false;
	}
}

void Test6Camera::Draw() {
	basicEffect->parameters.projection = camera->GetProjectionMatrix();
	basicEffect->parameters.view = camera->GetViewMatrix();
	basicEffect->parameters.world = VF::Math::rotate(VF::Math::Matrix4(1.0f), VF::Math::radians(90.0f), VF::Math::Vector3(1, 0, 0)) * VF::Math::translate(VF::Math::mat4(1.0f), VF::Math::Vector3(0, 0, 0));
	graphicsDevice->DrawPrimitives(vertexBuffer, basicEffect);
}

void Test6Camera::UpdateCamera() {
	VF::Input::Keyboard::GetState(window, keyboardState);
	VF::Input::Mouse::GetState(window, mouseState);
	camera->Move(window, keyboardState, mouseState);
	if (keyboardState.IsKeyDown(VF::Input::Keys::Escape)) {
		running = false;
	}
	camera->Update();
}

void Test6Camera::Shutdown() {
	graphicsDevice->Shutdown();
	windowManager->ShutDown();
}