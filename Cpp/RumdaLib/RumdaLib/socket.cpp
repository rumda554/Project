#include "pch.h"
namespace RumdaLib
{
	CSocket::CSocket()
	{
		_socket = -1;
	}

	CSocket::~CSocket()
	{
	}

	CSocket::CSocket(SOCKET socket)
	{
		_socket = socket;
	}

	bool CSocket::Connect()
	{
		return false;
	}

	bool CSocket::Bind()
	{
		return false;
	}

	bool CSocket::Listen()
	{
		return false;
	}

	bool CSocket::Accept()
	{
		return false;
	}

}

