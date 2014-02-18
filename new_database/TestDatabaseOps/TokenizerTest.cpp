#include "stdafx.h"
#include "CppUnitTest.h"
#include "Tokenizer.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TestDatabaseOps
{
	TEST_CLASS(TokenizerTest)
	{
	public:
		
		TEST_METHOD(TokenizerShouldSplitOnValidInputs) {
			Tokenizer tok;

			string input = "INSERT INTO species VALUES FROM RELATION project (kind) animals;";

			const char* args[] = { "INSERT", "INTO", "species", "VALUES", "FROM", "RELATION", "project", "(", "kind", ")", "animals", ";" };

			vector<string> expected_tokens(args, args + 12);
			tok.tokenizeInput(input);

			bool are_equal = true;

			for (unsigned int i = 0; i < expected_tokens.size(); i++) {
				if (expected_tokens.at(i) != tok.pop())
					are_equal = false;
			}

			Assert::AreEqual(are_equal, true);
		}

	};
}