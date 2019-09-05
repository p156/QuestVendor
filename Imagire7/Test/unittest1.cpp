#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

string vending()
{
	return "あなたは飛車角銀飛ばしでプレイしなければならない";
}

namespace Test
{		
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(test1)
		{
			Assert::AreEqual("あなたは飛車角銀飛ばしでプレイしなければならない", vending().c_str);
		}

	};
}