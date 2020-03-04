#pragma once
namespace RumdaLib
{
	class CSocket
	{
	public:
		CSocket();
		virtual ~CSocket();

	public:
		CSocket(SOCKET socket);

		bool Connect();
		bool Bind();
		bool Listen();
		bool Accept();

	private:
		SOCKET _socket; // 소켓 핸들
	};
}


