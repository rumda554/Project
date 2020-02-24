
#include "pch.h"
#include "CSingleton.h"

class CTest : public::CSingleton<CTest>
{
private:	

public:
	void TestMethod()
	{
		std::cout << "singleton test method";
	}
};

int main()
{
	std::cout << "Hello World!\n";

	auto pTst = CTest::GetInstance()->GetData();
	
	CTest::Instance().TestMethod();
	return 0;
}