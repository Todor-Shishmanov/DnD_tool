/*
#ifndef TEST_OBJ_HEADER
#define TEST_OBJ_HEADER
#include "CppUnitTest.h"
// Include your file
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests
{
	TEST_CLASS(Class Name)
	{
		TEST_METHOD(Method name)
		{
			Logger::WriteMessage(L"Testing wall.add_contained_object(key) with valid input:");

			// Do test

			Assert::IsTrue(added, L"wall.add_contained_object(key) unsuccessful: did not return true");
			Assert::IsTrue(contained[0] == &key, L"wall.add_contained_object(key) unsuccessful: did not add key to wall's objects");
			Assert::IsTrue(contained.size() == 1, L"wall.add_contained_object(key) unsuccessful: the count of contained objects is not 1");
			Assert::IsTrue(key.occupies() == &wall, L"wall.add_contained_object(key) unsuccessful: key does not occupy wall");
		}
	};

#endif // TEST_OBJ_HEADER

*/