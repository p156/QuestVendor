#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

string vending()
{
	return "���Ȃ��͔�Ԋp���΂��Ńv���C���Ȃ���΂Ȃ�Ȃ�";
}

namespace Test
{		
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(test1)
		{
			Assert::AreEqual("���Ȃ��͔�Ԋp���΂��Ńv���C���Ȃ���΂Ȃ�Ȃ�", vending().c_str);
		}

	};
}