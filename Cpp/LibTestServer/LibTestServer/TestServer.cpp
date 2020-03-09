#include "stdafx.h"

std::unordered_map<RemoteClient*, std::shared_ptr<RemoteClient>> remoteClients;


CTestServer::CTestServer()
{
}

CTestServer::~CTestServer()
{
}

bool CTestServer::Init()
{
	CIocp iocp;

	CSocket listenSocket(SocketType::Tcp);
	listenSocket.Bind(CEndpoint("0.0.0.0", 5555));
	listenSocket.Listen();

	iocp.Regist(listenSocket, nullptr);

	auto remoteClientCandidate = std::make_shared<RemoteClient>(SocketType::Tcp);

	listenSocket._isReadOverlapped = true;

	return false;
}

bool CTestServer::Run()
{
	return false;
}

bool CTestServer::Exit()
{
	return false;
}
