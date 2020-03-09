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

	bool Init();
	bool Run();
	bool Exit();

private:
	//...
};