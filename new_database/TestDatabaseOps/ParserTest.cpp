#include "stdafx.h"
#include "CppUnitTest.h"
#include "Parser.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TestDatabaseOps
{
	TEST_CLASS(ParserTest)
	{
	public:
		
		TEST_METHOD(ParserShouldCallCreateFunction)
		{
			Parser p;
			Assert::AreEqual((int)p.get_input_type(string(" CREATE TABLE <-select(kind==\"dogs\"animals")), (int)CREATE_);
		}

	};
}