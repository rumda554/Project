#pragma once
namespace RumdaLib
{
	enum class SocketType
	{
		Tcp,
		Udp,
	};

	class CEndpoint
	{
	public:
		CEndpoint();
		CEndpoint(const char* address, int port);
		~CEndpoint();

		static CEndpoint Any;
		sockaddr_in _endpoint; // ipv4
	};

	class CSocket
	{
	public:
		CSocket();
		~CSocket();

	public:
		CSocket(SocketType socketType);

		bool Connect(const CEndpoint& endpoint);
		bool Bind(const CEndpoint& endpoint);
		bool Accept(CSocket& acceptedSocket);
		void Listen();

	private:
		SOCKET _socket; // 소켓 핸들
	};
}


