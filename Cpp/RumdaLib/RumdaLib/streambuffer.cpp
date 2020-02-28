#include "pch.h"

namespace RumdaLib
{
	CStreamBuffer::CStreamBuffer()
	{
		_bufferPos = nullptr;
		_size = 0;
	}
	CStreamBuffer::~CStreamBuffer()
	{
	}
	bool CStreamBuffer::Set(uint8_t* buffer)
	{
		/*if (!buffer)
			return false;

		_bufferPos = buffer;*/
		_size = 0;

		return true;
	}
	bool CStreamBuffer::Set(char* buffer, int size)
	{
		if (!buffer)
			return false;

		_bufferPos = buffer;
		_size = size;

		return true;
	}
	char* CStreamBuffer::Get()
	{
		return _bufferPos;
	}
	uint32_t CStreamBuffer::Size()
	{
		return _size;
	}
	void CStreamBuffer::ReadData(bool* data)
	{
		memcpy(data, _bufferPos + _size, sizeof(bool)); // �д� �Լ��̹Ƿ� ���� �Ÿ� �ּ� ��ġ�� ���� �������� �ּҰ� �������� �ڷ��� ũ�⸸ŭ ī��
		_size -= sizeof(bool);							// �о���� ���̴� ũ�⸦ ����. ������ ���Ѵ�
	}
	void CStreamBuffer::ReadData(uint8_t* data)
	{
		memcpy(data, _bufferPos + _size, sizeof(uint8_t));
		_size -= sizeof(uint8_t);
	}
	void CStreamBuffer::ReadData(uint16_t* data)
	{
		memcpy(data, _bufferPos + _size, sizeof(uint16_t));
		_size -= sizeof(uint16_t);
	}
	void CStreamBuffer::ReadData(uint32_t* data)
	{
		memcpy(data, _bufferPos + _size, sizeof(uint32_t));
		_size -= sizeof(uint32_t);
	}
	void CStreamBuffer::ReadData(uint64_t* data)
	{
		memcpy(data, _bufferPos + _size, sizeof(uint64_t));
		_size -= sizeof(uint8_t);
	}
	void CStreamBuffer::ReadData(int* data)
	{
		memcpy(data, _bufferPos + _size, sizeof(int));
		_size -= sizeof(int);
	}
	void CStreamBuffer::ReadData(float* data)
	{
		memcpy(data, _bufferPos + _size, sizeof(float));
		_size -= sizeof(float);
	}
	void CStreamBuffer::ReadData(double* data)
	{
		memcpy(data, _bufferPos + _size, sizeof(double));
		_size -= sizeof(double);
	}
	void CStreamBuffer::ReadData(long double* data)
	{
		memcpy(data, _bufferPos + _size, sizeof(long double));
		_size -= sizeof(long double);
	}
	void CStreamBuffer::ReadData(std::string* data, int strSize)
	{
		// string �ڷ����� ī�Ǵ� ��Ʈ���� ���̸� �޾ƾ� �� ��? - �� ���� �����?
		memcpy(data, _bufferPos + _size, strSize);
		_size -= strSize;
	}
	void CStreamBuffer::ReadData(char* data)
	{
		memcpy(data, _bufferPos + _size, sizeof(char));
		_size -= sizeof(char);
	}

	void CStreamBuffer::WriteData(bool* data)
	{
		memcpy(_bufferPos + _size, &data, sizeof(bool)); // ���� �Լ��̹Ƿ� �о���� data�� �������� ���� �Ÿ� �ּ� ��ġ�� (���� ���� ��ġ+ũ��) �ڷ��� ũ�⸸ŭ ī��
		_size += sizeof(bool);
	}
	void CStreamBuffer::WriteData(uint8_t* data)
	{
		memcpy(_bufferPos + _size, &data, sizeof(uint8_t));
		_size += sizeof(uint8_t);
	}
	void CStreamBuffer::WriteData(uint16_t* data)
	{
		memcpy(_bufferPos + _size, &data, sizeof(uint16_t));
		_size += sizeof(uint16_t);
	}
	void CStreamBuffer::WriteData(uint32_t* data)
	{
		memcpy(_bufferPos + _size, &data, sizeof(uint32_t));
		_size += sizeof(uint32_t);
	}
	void CStreamBuffer::WriteData(uint64_t* data)
	{
		memcpy(_bufferPos + _size, &data, sizeof(uint64_t));
		_size += sizeof(uint64_t);
	}
	void CStreamBuffer::WriteData(int* data)
	{
		memcpy(_bufferPos + _size, &data, sizeof(int));
		_size += sizeof(int);
	}
	void CStreamBuffer::WriteData(float* data)
	{
		memcpy(_bufferPos + _size, &data, sizeof(float));
		_size += sizeof(float);
	}
	void CStreamBuffer::WriteData(double* data)
	{
		memcpy(_bufferPos + _size, &data, sizeof(double));
		_size += sizeof(double);
	}
	void CStreamBuffer::WriteData(long double* data)
	{
		memcpy(_bufferPos + _size, &data, sizeof(long double));
		_size += sizeof(long double);
	}
	void CStreamBuffer::WriteData(std::string* data, int strSize)
	{
		// �׽�Ʈ-Ȯ���ʿ�
		memcpy(_bufferPos + _size, &data, strSize);
		_size += strSize;
	}
	void CStreamBuffer::WriteData(char* data)
	{
		memcpy(_bufferPos + _size, &data, sizeof(char));
		_size += sizeof(char);
	}
}