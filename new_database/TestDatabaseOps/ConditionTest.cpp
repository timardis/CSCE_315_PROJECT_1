#include "stdafx.h"
#include "CppUnitTest.h"
#include "Condition.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TestDatabaseOps
{
	TEST_CLASS(ConditionTest)
	{
	public:

		TEST_METHOD(BothConditionsTrueShouldReturnTrue)
		{
			Tokenizer tok;
			tok.tokenizeInput("( age < 10 ) && ( name == \"Bob\" )");

			Condition c(tok);

			vector<Type> typeVec;
			typeVec.push_back(INTEGER);
			typeVec.push_back(VARCHAR);

			vector<string> attrVec;
			attrVec.push_back("age");
			attrVec.push_back("name");

			vector<string> valVec;
			valVec.push_back("9");
			valVec.push_back("Bob");

			Tuple tup(typeVec, attrVec, valVec);

			bool test = c.evaluate_tuple(tup);

			Assert::AreEqual(test, true);
		}

	};
}