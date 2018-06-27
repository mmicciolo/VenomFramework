#include "Test8Content.h"
#include "../../graphics/buffer/VertexDeclaration.h"
#include "../../graphics/buffer/IndexBuffer.h"
#include "../../graphics/model/Model.h"
#include "../../graphics/model/ModelMesh.h"
#include "../../content/Content.h"
#include "../../content/ModelContentLoader.h"

void Test8Content::LoadModel() {
	model = VF::Content::Content::Load<VF::Graphics::Model, VF::Content::ModelContentLoader>("HUD.x", graphicsDevice);
	animator = new VF::Graphics::Animator(model);
	VF::Content::ModelNode * node = model->modelNodesMap.at("$dummy_root");
	animator->Animate(node, VF::Math::Matrix4(1.0f), 0);
}

void Test8Content::SetupCamera() {
	VF::Camera::PerspectiveProjectionParameters parameters;
	parameters.fieldOfView = 45.0f;
	parameters.width = 640;
	parameters.height = 480;
	parameters.nearClip = 0.1f;
	parameters.farClip = 1000.0f;
	camera = new VF::Camera::FirstPersonCamera(parameters, VF::Math::Vector3(0, 0, -10), VF::Math::Vector3(0, 0, 0));
	VF::Input::Mouse::SetMouseInputMode(window, true, false);
}

void Test8Content::Init() {
	monitorManager = new VF::Window::MonitorManager();
	monitor = monitorManager->GetPrimaryMonitor();
	monitors = monitorManager->GetMonitors();
	windowManager = new VF::Window::WindowManager();
	window = new VF::Window::Window(640, 480, "Test 8 Content");
	windowManager->AddWindow(window);
	VF::Graphics::Viewport viewPort;
	graphicsDevice = new VF::Graphics::GraphicsDevice(window, viewPort);
	graphicsDevice->Init();
	SetupCamera();
	LoadModel();
}

void Test8Content::Update() {
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

void Test8Content::Draw() {
	model->Draw(camera->GetProjectionMatrix(), camera->GetViewMatrix(), VF::Math::Matrix4(1.0f));
}

void Test8Content::UpdateCamera() {
	VF::Input::Keyboard::GetState(window, keyboardState);
	VF::Input::Mouse::GetState(window, mouseState);
	camera->Move(window, keyboardState, mouseState);
	if (keyboardState.IsKeyDown(VF::Input::Keys::Escape)) {
		running = false;
	}
	if (keyboardState.IsKeyDown(VF::Input::Keys::Space)) {
		if (keyCount == 260) { keyCount = 0;  }
		animator->Animate(model->modelNodesMap.at("$dummy_root"), VF::Math::Matrix4(1.0f), keyCount);
		keyCount++;
	}
	camera->Update();
}

void Test8Content::Shutdown() {
	graphicsDevice->Shutdown();
	windowManager->ShutDown();
}