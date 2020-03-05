#include "pch.h"

namespace RumdaLib
{
	CIocp::CIocp()
	{
		SYSTEM_INFO SystemInfo;
		GetSystemInfo(&SystemInfo);

		_iocp = CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, 0, 0);
		_threadCount = SystemInfo.dwNumberOfProcessors * 2;
	}

	CIocp::~CIocp()
	{
		CloseHandle(_iocp);
	}

	bool CIocp::Regist(CSocket& socket, void* completionKey)
	{
		return CreateIoCompletionPort((HANDLE)socket._socket, _iocp, (ULONG_PTR)completionKey, _threadCount);
	}

	void CIocp::Work(CIocpEvent& output, int timeoutMs)
	{
		if (!GetQueuedCompletionStatusEx(_iocp, output._events, MaxEventCount, (ULONG*)&output._eventCount, timeoutMs, FALSE)) 
		{
			output._eventCount = 0;
		}
	}
}
