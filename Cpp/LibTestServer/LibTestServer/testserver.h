#pragma once

using namespace RumdaLib;

class RemoteClient
{
public:
	std::shared_ptr<std::thread> thread; // Ŭ���̾�Ʈ ó���� �ϴ� ������ 1��
	CSocket tcpConnection;		// accept�� TCP ����

	RemoteClient() {}
	RemoteClient(SocketType socketType) :tcpConnection(socketType) {}
};


// CTestServer, CGameServer, CLobbyServer, CChatServer ....
class CTestServer
{
public:
	CTestServer();
	virtual ~CTestServer();

	void Init();
	bool Run();
	void Exit();

private:
	//...
	CIocp iocp;
	CSocket listenSocket;
	std::shared_ptr<RemoteClient> remoteClientCandidate;
};