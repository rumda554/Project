#pragma once
namespace RumdaLib
{
	class Socket;

	class CIocp
	{
	public:
		CIocp(int threadCount);
		~CIocp();

		void Regist(Socket& socket, void* conpletionKey);
		void Work();

	private:
		HANDLE _iocp;
		int _threadCount;
	};
}