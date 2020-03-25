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
		int Send(const char* data, int length); // 패킷의 형태로 수정 필요
		void Close();

		void SetNagleOff();

		int UpdateAcceptContext(CSocket& listenSocket); //
		int ReceiveOverlapped(); //
		bool AcceptOverlapped(CSocket& acceptCandidateSocket);

	public:
		SOCKET _socket; // 소켓 핸들
		bool _isReadOverlapped = false;

		LPFN_ACCEPTEX AcceptEx = nullptr;
		static const int MaxReceiveLength = 8192;
		char _receiveBuffer[MaxReceiveLength];
		unsigned long _readFlags = 0;
		WSAOVERLAPPED _readOverlappedStruct;
	};
}


#pragma comment(lib, "Ws2_32.lib")
#pragma comment(lib, "mswsock.lib")

