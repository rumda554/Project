// LibTestServer.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//


#include "stdafx.h"

class CGameClass : public RumdaLib::CSingleton<CGameClass>
{
private:
public:
    CGameClass();
    ~CGameClass();
};


int main()
{
    std::cout << "Hello World!\n";
    auto v = RumdaLib::plus(1, 2);
}


// 코드 작성 후기
//1. 막상 라이브러리를 쓰려고 하면 해더파일과 라이브러리 프로젝트 후 빌드 된.lib 파일이 필요함

//2. 템플릿으로 작성되는 코드는 해더와 cpp를 분리하기 불가능 하므로 hpp로 작성하고 (C++ style) 하나로 묶어야 함.
//2-1. 다른 방법도 있겠지만 너무 불편할듯..

//3. 라이브러리 개발과 테스트 중에는 라이브러리 작성후 빌드 그리고 테스트할 프로젝트에 배포 하는 과정이 너무 불편함.

//4. 라이브러리를 써서 얻는 장점 (cpp파일을 가릴 수 있다.) (나중에 복잡한 cpp단을 알 필요가 없음)
//4-1. 장점에 비해 단점이 더 불편한 느낌..