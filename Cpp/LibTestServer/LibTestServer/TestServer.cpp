#include "stdafx.h"

std::unordered_map<RemoteClient*, std::shared_ptr<RemoteClient>> remoteClients;


CTestServer::CTestServer()
{
	// ������ �޼��带 �����ϴ°� �� ������. start����
	CIocp iocp2;
	iocp = iocp2; // ..?

	CSocket socket(SocketType::Tcp);
	listenSocket = socket;

	remoteClientCandidate = std::make_shared<RemoteClient>(SocketType::Tcp);
}

CTestServer::~CTestServer()
{
}

void CTestServer::Init()
{
	listenSocket.Bind(CEndpoint("0.0.0.0", 5555));
	listenSocket.Listen();

	iocp.Regist(listenSocket, nullptr);

	listenSocket._isReadOverlapped = true;
}

// �ڷ� ������ testserver prototype. ��ɰ��� �� �߰��� ������ �ִ��� üũ�غ���
bool CTestServer::Run()
{
	CIocpEvent readEvents;
	iocp.Work(readEvents, 100);

	for (int i = 0; i < readEvents._eventCount; i++)
	{
		auto& readEvent = readEvents._events[i];
		if (readEvent.lpCompletionKey == 0) // ���� ����
		{
			listenSocket._isReadOverlapped = false;
			// Win32 AcceptEx 
			if (remoteClientCandidate->tcpConnection.UpdateAcceptContext(listenSocket) != 0)
			{
				listenSocket.Close();
			}
			else
			{
				auto remoteClient = remoteClientCandidate;
				iocp.Regist(remoteClient->tcpConnection, remoteClient.get());

				if (remoteClient->tcpConnection.ReceiveOverlapped() != 0 && WSAGetLastError() != ERROR_IO_PENDING)
				{
					// error. ������ ��������. �׸��� �׳� ������.
					remoteClient->tcpConnection.Close();
				}
				else
				{
					remoteClient->tcpConnection._isReadOverlapped = true;
					remoteClients.insert({ remoteClient.get(), remoteClient });
				}

				// ����ؼ� ���� �ޱ⸦ �ؾ� �ϹǷ� �������ϵ� overlapped I/O�� ����.
				remoteClientCandidate = std::make_shared<RemoteClient>(SocketType::Tcp);
				if (!listenSocket.AcceptOverlapped(remoteClientCandidate->tcpConnection) && WSAGetLastError() != ERROR_IO_PENDING)
				{
					// error. �������� �������� �Ҵ� ���·� ������. 
					listenSocket.Close();
				}
				else
				{
					// ���������� ������ ������ ��ٸ��� ���°� �Ǿ���.
					listenSocket._isReadOverlapped = true;
				}
			}
		}
		else  // TCP ���� �����̸�
		{
			// ���� �����͸� �״�� ȸ���Ѵ�. - �������� ó�� �ʿ�
			auto remoteClient = remoteClients[(RemoteClient*)readEvent.lpCompletionKey];

			if (readEvent.dwNumberOfBytesTransferred <= 0)
			{
				int a = 0;
			}

			if (remoteClient)
			{
				// �̹� ���ŵ� �����̴�. ���� �Ϸ�� ���� �׳� ���� ����.
				remoteClient->tcpConnection._isReadOverlapped = false;
				int ec = readEvent.dwNumberOfBytesTransferred;

				if (ec <= 0)
				{
					// error
					//ProcessClientLeave(remoteClient);
				}
				else
				{
					// �̹� ���ŵ� �����̴�. ���� �Ϸ�� ���� �׳� ���� ����.
					char* echoData = remoteClient->tcpConnection._receiveBuffer;
					int echoDataLength = ec;

					remoteClient->tcpConnection.Send(echoData, echoDataLength);

					if (remoteClient->tcpConnection.ReceiveOverlapped() != 0 && WSAGetLastError() != ERROR_IO_PENDING)
					{
						//ProcessClientLeave(remoteClient);
						return false; // error
					}
					else
					{
						remoteClient->tcpConnection._isReadOverlapped = true;
					}
				}
			}
		}
	}

	return true;
}

void CTestServer::Exit()
{
	listenSocket.Close();
	for (auto i : remoteClients)
	{
		i.second->tcpConnection.Close();
	}

	// cout << "������ �����ϰ� �ֽ��ϴ�...\n";
	while (remoteClients.size() > 0 || listenSocket._isReadOverlapped)
	{
		for (auto i = remoteClients.begin(); i != remoteClients.end();)
		{
			if (!i->second->tcpConnection._isReadOverlapped)
			{
				i = remoteClients.erase(i);
			}
			else
				i++; // �� �� ��ٷ�����.
		}

		CIocpEvent readEvents;
		iocp.Work(readEvents, 100);

		// ���� �̺�Ʈ ������ ó���մϴ�.
		for (int i = 0; i < readEvents._eventCount; i++)
		{
			auto& readEvent = readEvents._events[i];
			if (readEvent.lpCompletionKey == 0) // ���������̸�
			{
				listenSocket._isReadOverlapped = false;
			}
			else
			{
				auto remoteClient = remoteClients[(RemoteClient*)readEvent.lpCompletionKey];
				if (remoteClient)
				{
					remoteClient->tcpConnection._isReadOverlapped = false;
				}
			}
		}
	}

	// cout << "���� ����\n";
}
