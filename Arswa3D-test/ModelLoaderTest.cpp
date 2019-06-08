#include "stdafx.h"
#include "CppUnitTest.h"
#include <crtdbg.h>

#include "../OpenGL-Tutorial/ModelLoader.h"
#include "../OpenGL-Tutorial/ModelLoader.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

struct CrtCheckMemory {
	// Heap Memory test from stackoverflow
	// https://stackoverflow.com/questions/2980917/c-is-it-possible-to-implement-memory-leak-testing-in-a-unit-test
	_CrtMemState state1;
	_CrtMemState state2;
	_CrtMemState state3;
	CrtCheckMemory()
	{
		_CrtMemCheckpoint(&state1);
	}
	~CrtCheckMemory()
	{
		_CrtMemCheckpoint(&state2);
		// using google test you can just do this.
		Assert::AreEqual(0, _CrtMemDifference(&state3, &state1, &state2));
		// else just do this to dump the leaked blocks to stdout.
		if (_CrtMemDifference(&state3, &state1, &state2))
			_CrtMemDumpStatistics(&state3);
	}
};

namespace Arswa3Dtest
{
	TEST_CLASS(ModelLoaderTest)
	{
	public:

		TEST_METHOD(GetInstanceTest)
		{
			ModelLoader* loader = ModelLoader::getInstance();
			Assert::IsNotNull(loader);
		}

		TEST_METHOD(LoadStaticModels)
		{
			ModelLoader* loader = ModelLoader::getInstance();
			Model* model1 = loader->loadModel("Models/platform/roof.obj");
			Model* model2 = loader->loadModel("Models/platform/platform2.obj");
			Model* model3 = loader->loadModel("Models/platform/wall.obj");
			Assert::IsNotNull(model1);
			Assert::IsNotNull(model2);
			Assert::IsNotNull(model3);
		}

		TEST_METHOD(ModelLoadingMemoryLeaking)
		{
			ModelLoader* loader = ModelLoader::getInstance();
			// Memory check start after the test as we don't want to take into account the ModelLoader initialisation
			CrtCheckMemory check;
			Model* model1 = loader->loadModel("Models/platform/roof.obj");
			delete model1;
		}

	};
}