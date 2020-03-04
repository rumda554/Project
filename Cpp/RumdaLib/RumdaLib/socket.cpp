#include "pch.h"
namespace RumdaLib
{
	CSocket::CSocket()
	{
		_socket = -1;
	}

	CSocket::~CSocket()
	{
		closesocket(_socket);
	}

	CSocket::CSocket(SocketType socketType)
	{
		if (socketType == SocketType::Tcp)
		{
			//_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
			// iocp�� ���� ���ؼ� �� �Լ��� �� - window ����
			_socket = WSASocket(AF_INET, SOCK_STREAM, IPPROTO_TCP, NULL, 0, WSA_FLAG_OVERLAPPED);
		}
		else
		{
			//_socket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
			_socket = WSASocket(AF_INET, SOCK_DGRAM, IPPROTO_UDP, NULL, 0, WSA_FLAG_OVERLAPPED);
		}
	}

	bool CSocket::Connect(const CEndpoint& endpoint)
	{
		// -1 �̸� ���Ͽ��� 0 ���ϸ� ���� �߸��Ȱ���
		return connect(_socket, (sockaddr*)&endpoint._endpoint, sizeof(endpoint._endpoint));
	}

	bool CSocket::Bind(const CEndpoint& endpoint)
	{
		// -1 �̸� ���Ͽ��� 0 ���ϸ� ���� �߸��Ȱ���
		return bind(_socket, (sockaddr*)&endpoint._endpoint, sizeof(endpoint._endpoint));
	}

	void CSocket::Listen()
	{
		listen(_socket, SOMAXCONN);
	}

	bool CSocket::Accept(CSocket& acceptedSocket)
	{
		acceptedSocket._socket = accept(_socket, nullptr, 0);
		return (acceptedSocket._socket == -1) ? false : true;
	}

	CEndpoint::CEndpoint()
	{
		memset(&_endpoint, 0, sizeof(_endpoint));
		_endpoint.sin_family = AF_INET;
	}

	CEndpoint::CEndpoint(const char* address, int port)
	{
		memset(&_endpoint, 0, sizeof(_endpoint));
		_endpoint.sin_family = AF_INET;

		inet_pton(AF_INET, address, &_endpoint.sin_addr);
		_endpoint.sin_port = htons((uint16_t)port);
	}

	CEndpoint::~CEndpoint()
	{
	}

	CEndpoint CEndpoint::Any;
}

