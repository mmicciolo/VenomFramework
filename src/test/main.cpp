#include <vector>

#include "ITest.h"
#include "Test1 (Window)\Test1Window.h"
#include "Test2 (Input)\Test2Input.h"
#include "Test3 (GraphicsDevice)\Test3GraphicsDevice.h"
#include "Test4 (VertexBuffer)\Test4VertexBuffer.h"
#include "Test5 (IndexBuffer)\Test5IndexBuffer.h"
#include "Test6 (Camera)\Test6Camera.h"
#include "Test7 (Model)\Test7Model.h"
#include "Test8 (Content)\Test8Content.h"

namespace TestTypes {
	enum Types {
		Test1Window,
		Test2Input,
		Test3GraphicsDevice,
		Test4VertexBuffer,
		Test5IndexBuffer,
		Test6Camera,
		Test7Model,
		Test8Content
	};
}


std::vector<ITest *> tests;
TestTypes::Types testType = TestTypes::Test4VertexBuffer;

void SetupTests() {
	tests.push_back(new Test1Window());
	tests.push_back(new Test2Input());
	tests.push_back(new Test3GraphicsDevice());
	tests.push_back(new Test4VertexBuffer());
	tests.push_back(new Test5IndexBuffer());
	tests.push_back(new Test6Camera());
	tests.push_back(new Test7Model());
	tests.push_back(new Test8Content());
}

int main() {

	SetupTests();

	ITest * test = tests.at(testType);

	test->Init();

	while (test->Running()) {
		test->Update();
	}

	test->Shutdown();
}