#pragma once

using namespace RumdaLib;

class RemoteClient
{
public:
	std::shared_ptr<std::thread> thread; // 클라이언트 처리를 하는 스레드 1개
	CSocket tcpConnection;		// accept한 TCP 연결

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