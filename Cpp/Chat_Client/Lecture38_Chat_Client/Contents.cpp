#include "stdafx.h"
#include "Contents.h"
#include "Packet.h"
#include "PacketProc.h"
#include "Network.h"

void MakeRoom(wchar_t* roomName)
{
	CPacket cPacket;
	PacketCreate_CreateRoom(&cPacket, roomName);

	SendPacket(&cPacket);
}

void CreateRoom(wchar_t* roomName)
{
	
}