#include "stdafx.h"
#include "CppUnitTest.h"
#include "Tuple.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace DatabaseTest
{		
	TEST_CLASS(TypeTest) {
	public:
		
		TEST_METHOD(VarcharTypesShouldNotEqualIntegerTypes) {
			Type t1(false);
			Type t2(8, false);
			Assert::AreEqual(t1 == t2, false);
		}

		TEST_METHOD(VarcharTypesOfDifferentLengthShouldNotBeEqual) {
			Type t1(1, false);
			Type t2(2, false);
			Assert::AreEqual(t1==t2, false);
		}

		TEST_METHOD(IntegerTypesShouldBeEqual) {
			Type t1(false);
			Type t2(false);
			Assert::AreEqual(t1==t2, true);
		}

		TEST_METHOD(VarcharTypesOfSameLengthShouldBeEqual) {
			Type t1(1, false);
			Type t2(1, false);
			Assert::AreEqual(t1==t2, true);
		}
	};

	TEST_CLASS(ConditionTest) {
	public:
		TEST_METHOD(EqualPairsShouldTestEqual) {

		}
	};

	TEST_CLASS(PairTest) {
	public:
		TEST_METHOD(EqualPairsShouldBeEqual) {
			Pair p1(Type(false), "name", "Bob");
			Pair p2(Type(false), "name", "Bob");

			Assert::AreEqual(p1 == p2, true);
		}

		TEST_METHOD(PairsWithDifferentValuesShouldNotBeEqual) {
			Pair p1(Type(false), "name", "Bob");
			Pair p2(Type(false), "name", "Joe");

			Assert::AreNotEqual(p1 == p2, true);
		}

		TEST_METHOD(PairsWithDifferentTypesShouldNotBeEqual) {
			Pair p1(Type(false), "name", "Bob");
			Pair p2(Type(1, false), "name", "Bob");

			Assert::AreNotEqual(p1 == p2, true);
		}

		TEST_METHOD(PairsWithDifferentAttributesShouldNotBeEqual) {
			Pair p1(Type(false), "name", "Bob");
			Pair p2(Type(false), "nickname", "Bob");

			Assert::AreNotEqual(p1 == p2, true);
		}
	};
}