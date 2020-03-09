#pragma once
namespace RumdaLib
{
	class CSocket;
	class CIocpEvent;

	class CIocp
	{
	public:
		CIocp();
		~CIocp();

		bool Regist(CSocket& socket, void* completionKey);
		void Work(CIocpEvent& output, int timeoutMs);

	public:
		static const int MaxEventCount = 100;

	private:
		HANDLE _iocp;
		int _threadCount;
	};

	class CIocpEvent
	{
	public:
		
		// GetQueuedCompletionStatus���� ������ �̺�Ʈ��
		OVERLAPPED_ENTRY _events[CIocp::MaxEventCount];
		int _eventCount;
	};
}