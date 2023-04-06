#include "CppUnitTest.h"
#include "../Code/dummy.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest
{
	TEST_CLASS(CombatAttributesTest)
	{
		TEST_METHOD(dummy_method)
		{
			Assert::IsTrue(ret_true());
		}
	};
}