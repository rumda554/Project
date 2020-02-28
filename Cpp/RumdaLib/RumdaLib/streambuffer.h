#pragma once
namespace RumdaLib
{
	class CStreamBuffer
	{
	public:
		CStreamBuffer();
		virtual ~CStreamBuffer();

	public:
		bool Set(uint8_t* buffer);
		bool Set(char* buffer, int size);
		//uint8_t* Get();
		char* Get();
		uint32_t Size();

		void ReadData(bool* data);
		void ReadData(uint8_t* data);
		void ReadData(uint16_t* data);
		void ReadData(uint32_t* data);
		void ReadData(uint64_t* data);
		void ReadData(int* data);
		void ReadData(float* data);
		void ReadData(double* data);
		void ReadData(long double* data);
		void ReadData(std::string* data, int strSize);
		void ReadData(char* data);
		// 복합적인 자료형 (템플릿, 구조체 등의 자료를 읽고 쓸 수 있어야 할까?)
		
		void WriteData(bool* data);
		void WriteData(uint8_t* data);
		void WriteData(uint16_t* data);
		void WriteData(uint32_t* data);
		void WriteData(uint64_t* data);
		void WriteData(int* data);
		void WriteData(float* data);
		void WriteData(double* data);
		void WriteData(long double* data);
		void WriteData(std::string* data, int strSize);
		void WriteData(char* data);

	private:
		//uint8_t* _bufferPos; // 버퍼의 위치
		char* _bufferPos;
		uint64_t _size;		// 크기
	};
}