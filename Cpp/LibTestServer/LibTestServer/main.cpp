﻿// LibTestServer.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//


#include "stdafx.h"

class CGameClass : public RumdaLib::CSingleton<CGameClass>
{
private:
public:
	CGameClass();
	~CGameClass();
};

// 결국 목표는 오브젝트 풀
class CTestMemoryPool :public RumdaLib::CMemoryPool<CTestMemoryPool>
{
public:
	int8_t a[1024];
	int8_t b[1024];
};

// 메모리 풀을 안쓰는 클래스
class CTestMemoryPool2
{
public:
	int8_t a[1024];
	int8_t b[1024];
};


int main()
{
	std::cout << "Hello World!\n";
	auto v = RumdaLib::plus(1, 2);

	int loopCnt = 1000000;

	auto startT = std::chrono::system_clock::now();

	for (int i = 0; i < loopCnt; i++)
	{
		auto* p = new CTestMemoryPool(); // case1 (65000 ms)
		//auto* p = new CTestMemoryPool2(); // case2 (329000 ms)
		delete p;
	}

	auto endT = std::chrono::system_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(endT - startT).count();
	std::cout << "Took" << duration << "Millisec" << std::endl;


	// int형 데이터 3개 혹은 패킷 데이터를 메모리 버퍼에 쌓아야 할때
	auto memoryBuffer = new char[100]; // 100바이트 짜리 버퍼가 있다 치자

	// 예를 들어 패킷으로 int 형 자료 3개가 왔다 친다
	int userlevel = 11;
	int itemlevel = 22;
	int status = 1;

	// 메모리 버퍼에 쌓기 - 쓰기도 불편하고 유지보수가 어려움
	memcpy(memoryBuffer, &userlevel, sizeof(int));
	memcpy(memoryBuffer + sizeof(int), &itemlevel, sizeof(int));
	memcpy(memoryBuffer + sizeof(int) + sizeof(int), &status, sizeof(int));
	// 이시점의 디버깅으로 메모리값 확인 
	// 0b 00 00 00 16 00 00 00 01 00 00 00 cd cd cd cd cd ....
	// 11          22           1          초기화 되지 않은 값
          
	
	// 스트림버퍼 클래스를 이용한 방법
	RumdaLib::CStreamBuffer stream;
	auto memoryBuffer2 = new char[100];

	stream.Set(memoryBuffer2);
	stream.WriteData(&userlevel); // 쓸때 버퍼를 늘리고 값을 채움
	stream.WriteData(&itemlevel);
	stream.WriteData(&status);
	// 메모리값 일치함을 확인
	// 0b 00 00 00 16 00 00 00 01 00 00 00 cd cd cd cd cd


	delete[] memoryBuffer;

	delete[] memoryBuffer2;
}

// 초기프로젝트 구성 작성 후기
//1. 막상 라이브러리를 쓰려고 하면 해더파일과 라이브러리 프로젝트 후 빌드 된.lib 파일이 필요함
//2. 템플릿으로 작성되는 코드는 해더와 cpp를 분리하기 불가능 하므로 hpp로 작성하고 (C++ style) 하나로 묶어야 함.
//2-1. 다른 방법도 있겠지만 너무 불편할듯..
//3. 라이브러리 개발과 테스트 중에는 라이브러리 작성후 빌드 그리고 테스트할 프로젝트에 배포 하는 과정이 너무 불편함.
//4. 라이브러리를 써서 얻는 장점 (cpp파일을 가릴 수 있다.) (나중에 복잡한 cpp단을 알 필요가 없음)
//4-1. 장점에 비해 단점이 더 불편한 느낌..



// memoryPool 작성 후기(책기반)
// 반복적인 new 와 delete시 프로그램의 속도에 영향이 미친다
// 미리 커다랗게 (객체 크기 * 임의로 정한 블록사이즈) 메모리 할당을 해놓고
// 메모리 할당이 오면 그 풀(메모리풀) 객체에 붙이면 객체 풀 끄내고 넣는다.

// 템플릿으로 감싸서 어떤 객체형이 와도 그 크기만큼 할당하게 하였다.
// new와 delete 연산자 오퍼레이팅을 통하여 연산자를 쓰듯 자연스럽게 사용하게 하였다.

// 일단은 인터넷에 있는 코드를 참조했고 실제로 성능상의 확인은 되었다.
// 추가 궁금점.
// 멀티스레드 상황에서의 메모리 할당과 해제는 안전한가?
// 기타 라이브러리 (boost, TBB)와 같은 라이브러리는 어떤가?
// 다른 방식으로 구현한 메모리 풀도 참조해보자.
// 그냥 new와 delete 는 정말 성능이 구린걸까?



// 부스트 라이브러리 적용 서버 작성 후기
// 1. 단순 에코 서버를 유연한 형태의 서버를 만들 수 있는 구조로 변경 필요
// 2. 링크 에러 발생 (임시 커밋 포함 제외)
// 3. boost package를 전부 포함시키지 않는 방법? (용량), 
// 3-1. 라이브러리 프로젝트에도 패키지를 포함했는데 서버에도 패키지를 포함하긴 좀 그렇다.



// streamBuffer 작성 후기
// 정렬되서 오는 다양한 자료형의 패킷을 하나의 메모리버퍼에 쌓고 읽는 작업을 확인하였다.
// 조금 더 유연한 형태로 받아들일 수 있는 방법이 있는지 개선점 찾기
// 코드 중복이 많은데 어쩔 수 없나?
// string, struct, vector List<Object>와 같은 복합적인 패킷 자료형이 왔을때의 대처 방법은?

