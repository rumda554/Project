#include "pch.h"

namespace RumdaLib
{
	CStreamBuffer::CStreamBuffer()
	{
		_pos = 0;
		_size = 0;
	}
	CStreamBuffer::~CStreamBuffer()
	{
	}
	bool CStreamBuffer::Set(char* buffer)
	{
		if (!buffer)
			return false;

		_data = buffer;
		_pos = 0;
		_size = 0;

		return true;
	}
	char* CStreamBuffer::Get()
	{
		return _data;
	}
	uint32_t CStreamBuffer::Size()
	{
		return _size;
	}
	void CStreamBuffer::ReadData(bool* data)
	{
		memcpy(data, &_data[_pos], sizeof(bool));
		_pos -= sizeof(bool);
		_size = _pos;			// �о���� ���̴� ũ�⸦ ����. ������ ���Ѵ�
	}
	void CStreamBuffer::ReadData(uint8_t* data)
	{
		memcpy(data, &_data[_pos], sizeof(uint8_t));
		_pos -= sizeof(uint8_t);
		_size = _pos;
	}
	void CStreamBuffer::ReadData(uint16_t* data)
	{
		memcpy(data, &_data[_pos], sizeof(uint16_t));
		_pos -= sizeof(uint16_t);
		_size = _pos;
	}
	void CStreamBuffer::ReadData(uint32_t* data)
	{
		memcpy(data, &_data[_pos], sizeof(uint32_t));
		_pos -= sizeof(uint32_t);
		_size = _pos;
	}
	void CStreamBuffer::ReadData(uint64_t* data)
	{
		memcpy(data, &_data[_pos], sizeof(uint64_t));
		_pos -= sizeof(uint64_t);
		_size = _pos;
	}
	void CStreamBuffer::ReadData(int* data)
	{
		memcpy(data, &_data[_pos], sizeof(int));
		_pos -= sizeof(int);
		_size = _pos;
	}
	void CStreamBuffer::ReadData(float* data)
	{
		memcpy(data, &_data[_pos], sizeof(float));
		_pos -= sizeof(float);
		_size = _pos;
	}
	void CStreamBuffer::ReadData(double* data)
	{
		memcpy(data, &_data[_pos], sizeof(double));
		_pos -= sizeof(double);
		_size = _pos;
	}
	void CStreamBuffer::ReadData(long double* data)
	{
		memcpy(data, &_data[_pos], sizeof(long double));
		_pos -= sizeof(long double);
		_size = _pos;
	}
	void CStreamBuffer::ReadData(std::string* data, int strSize)
	{
		// string �ڷ����� ī�Ǵ� ��Ʈ���� ���̸� �޾ƾ� �� ��? - �� ���� �����?
		memcpy(data, &_data[_pos], strSize);
		_pos -= strSize;
		_size = _pos;
	}
	void CStreamBuffer::ReadData(char* data)
	{
		memcpy(data, &_data[_pos], sizeof(char));
		_pos -= sizeof(char);
		_size = _pos;
	}

	void CStreamBuffer::WriteData(bool* data)
	{
		memcpy(&_data[_pos], data, sizeof(bool));
		_pos += sizeof(bool);
		_size = _pos;
	}
	void CStreamBuffer::WriteData(uint8_t* data)
	{
		memcpy(&_data[_pos], data, sizeof(uint8_t));
		_pos += sizeof(uint8_t);
		_size = _pos;
	}
	void CStreamBuffer::WriteData(uint16_t* data)
	{
		memcpy(&_data[_pos], data, sizeof(uint16_t));
		_pos += sizeof(uint16_t);
		_size = _pos;
	}
	void CStreamBuffer::WriteData(uint32_t* data)
	{
		memcpy(&_data[_pos], data, sizeof(uint32_t));
		_pos += sizeof(uint32_t);
		_size = _pos;
	}
	void CStreamBuffer::WriteData(uint64_t* data)
	{
		memcpy(&_data[_pos], data, sizeof(uint64_t));
		_pos += sizeof(uint64_t);
		_size = _pos;
	}
	void CStreamBuffer::WriteData(int* data)
	{
		memcpy(&_data[_pos], data, sizeof(int));
		_pos += sizeof(int);
		_size = _pos;
	}
	void CStreamBuffer::WriteData(float* data)
	{
		memcpy(&_data[_pos], data, sizeof(float));
		_pos += sizeof(float);
		_size = _pos;
	}
	void CStreamBuffer::WriteData(double* data)
	{
		memcpy(&_data[_pos], data, sizeof(double));
		_pos += sizeof(double);
		_size = _pos;
	}
	void CStreamBuffer::WriteData(long double* data)
	{
		memcpy(&_data[_pos], data, sizeof(long double));
		_pos += sizeof(long double);
		_size = _pos;
	}
	void CStreamBuffer::WriteData(std::string* data, int strSize)
	{
		// �׽�Ʈ-Ȯ���ʿ�
		memcpy(&_data[_pos], data, strSize);
		_pos += strSize;
		_size = _pos;
	}
	void CStreamBuffer::WriteData(char* data)
	{
		memcpy(&_data[_pos], data, sizeof(char));
		_pos += sizeof(char);
		_size = _pos;
	}
}