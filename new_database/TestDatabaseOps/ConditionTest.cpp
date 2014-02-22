#include "stdafx.h"
#include "CppUnitTest.h"
#include "Condition.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TestDatabaseOps
{
	TEST_CLASS(ConditionTest)
	{
	public:
		TEST_METHOD(AND_BothConditionsTrueShouldReturnTrue) {
			Tokenizer tok;
			tok.tokenize_input("(( age < 10 ) && ( name == \"Bob\" ))");

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

		TEST_METHOD(AND_OneConditionTrueShouldReturnFalse) {
			Tokenizer tok;
			tok.tokenize_input("(( age > 10 ) && ( name == \"Bob\" ))");

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

			Assert::AreEqual(test, false);
		}

		TEST_METHOD(AND_NoConditionsTrueShouldReturnFalse) {
			Tokenizer tok;
			tok.tokenize_input("(( age > 10 ) && ( name == \"Joe\" ))");

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
			Assert::AreEqual(test, false);
		}

		TEST_METHOD(OR_BothConditionsTrueShouldReturnTrue) {
			Tokenizer tok;
			tok.tokenize_input("(( age < 10 ) || ( name == \"Bob\" ))");

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

		TEST_METHOD(OR_OneConditionTrueShouldReturnTrue) {
			Tokenizer tok;
			tok.tokenize_input("(( age > 10 ) || ( name == \"Bob\" ))");

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

		TEST_METHOD(OR_NoConditionTrueShouldReturnFalse) {
			Tokenizer tok;
			tok.tokenize_input("(( age > 10 ) || ( name == \"Joe\" ))");

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
			Assert::AreEqual(test, false);
		}
	};
}