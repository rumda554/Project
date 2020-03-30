#pragma once
namespace RumdaLib
{
	enum class SocketType
	{
		Tcp,
		Udp,
	};

	class Endpoint
	{
	public:
		Endpoint();
		Endpoint(const char* address, int port);
		~Endpoint();

		static Endpoint Any;
		sockaddr_in _endpoint; // ipv4
	};

	class Socket
	{
	public:
		Socket();
		~Socket();

	public:
		Socket(SocketType socketType);

		bool Connect(const Endpoint& endpoint);
		bool Bind(const Endpoint& endpoint);
		bool Accept(Socket& acceptedSocket);
		void Listen();
		int Send(const char* data, int length); // ��Ŷ�� ���·� ���� �ʿ�
		void Close();

		void SetNagleOff();

		int UpdateAcceptContext(Socket& listenSocket); //
		int ReceiveOverlapped(); //
		bool AcceptOverlapped(Socket& acceptCandidateSocket);

	public:
		SOCKET _socket; // ���� �ڵ�
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

