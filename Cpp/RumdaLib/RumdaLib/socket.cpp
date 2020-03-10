#include "pch.h"
namespace RumdaLib
{
	CSocket::CSocket()
	{
		_socket = -1;
		memset(&_readOverlappedStruct, 0, sizeof(_readOverlappedStruct));
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
			// iocp를 쓰기 위해선 이 함수를 씀 - window 전용
			_socket = WSASocket(AF_INET, SOCK_STREAM, IPPROTO_TCP, NULL, 0, WSA_FLAG_OVERLAPPED);
		}
		else
		{
			//_socket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
			_socket = WSASocket(AF_INET, SOCK_DGRAM, IPPROTO_UDP, NULL, 0, WSA_FLAG_OVERLAPPED);
		}

		memset(&_readOverlappedStruct, 0, sizeof(_readOverlappedStruct));
	}

	bool CSocket::Connect(const CEndpoint& endpoint)
	{
		// -1 이면 소켓에러 0 이하면 뭔가 잘못된거임
		return connect(_socket, (sockaddr*)&endpoint._endpoint, sizeof(endpoint._endpoint));
	}

	bool CSocket::Bind(const CEndpoint& endpoint)
	{
		// -1 이면 소켓에러 0 이하면 뭔가 잘못된거임
		return bind(_socket, (sockaddr*)&endpoint._endpoint, sizeof(endpoint._endpoint));
	}

	bool CSocket::Accept(CSocket& acceptedSocket)
	{
		acceptedSocket._socket = accept(_socket, nullptr, 0);
		return (acceptedSocket._socket == -1) ? false : true;
	}

	void CSocket::Listen()
	{
		listen(_socket, SOMAXCONN);
	}

	int CSocket::Send(const char* data, int length)
	{
		return send(_socket, data, length, 0);
	}

	void CSocket::Close()
	{
		closesocket(_socket);
	}

	void CSocket::SetNagleOff()
	{
		bool option = true;
		setsockopt(_socket, IPPROTO_TCP, TCP_NODELAY, (const char*)&option, sizeof(option));
	}

	int CSocket::UpdateAcceptContext(CSocket& listenSocket)
	{
		sockaddr_in ignore1;
		sockaddr_in ignore3;
		INT ignore2, ignore4;

		char ignore[1000];
		GetAcceptExSockaddrs(ignore, 0, 50, 50, (sockaddr**)&ignore1, &ignore2, (sockaddr**)&ignore3, &ignore4);

		return setsockopt(_socket, SOL_SOCKET, SO_UPDATE_ACCEPT_CONTEXT, (char*)&listenSocket._socket, sizeof(listenSocket._socket));
	}

	int CSocket::ReceiveOverlapped()
	{
		WSABUF b;
		b.buf = _receiveBuffer;
		b.len = MaxReceiveLength;

		_readFlags = 0;

		return WSARecv(_socket, &b, 1, NULL, &_readFlags, &_readOverlappedStruct, NULL);
	}

	bool CSocket::AcceptOverlapped(CSocket& acceptCandidateSocket)
	{
		if (AcceptEx == NULL)
		{
			DWORD bytes;
			WSAIoctl(_socket, SIO_GET_EXTENSION_FUNCTION_POINTER, &UUID(WSAID_ACCEPTEX), sizeof(UUID), &AcceptEx, sizeof(AcceptEx), &bytes, NULL, NULL);

			if (AcceptEx == NULL)
			{
				//throw Exception("Getting AcceptEx ptr failed.");
				return false; // error
			}
		}

		// 여기에는 accept된 소켓의 로컬주소와 리모트주소가 현재는 버림 - 차후 채크
		char ignored[200];
		DWORD ignored2 = 0;

		bool ret = AcceptEx(_socket, acceptCandidateSocket._socket, &ignored, 0, 50, 50, &ignored2, &_readOverlappedStruct) == TRUE;
		return ret;
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

