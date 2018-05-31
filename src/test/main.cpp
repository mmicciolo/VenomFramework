#include <vector>

#include "ITest.h"
#include "Test1 (Window)\Test1Window.h"
#include "Test2 (Input)\Test2Input.h"
#include "Test3 (GraphicsDevice)\Test3GraphicsDevice.h"
#include "Test4 (VertexBuffer)\Test4VertexBuffer.h"

namespace TestTypes {
	enum Types {
		Test1Window,
		Test2Input,
		Test3GraphicsDevice,
		Test4VertexBuffer
	};
}


std::vector<ITest *> tests;
TestTypes::Types testType = TestTypes::Test4VertexBuffer;

void SetupTests() {
	tests.push_back(new Test1Window());
	tests.push_back(new Test2Input());
	tests.push_back(new Test3GraphicsDevice());
	tests.push_back(new Test4VertexBuffer());
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