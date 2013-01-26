//
//  Atrium
//  Ben Maher
//
//  2013(c) - GNU GPL V3
//
//  File Name   :   networkplayer.cpp
//  Description :   A networked player object.
//  Author      :   Ben Maher
// 

// Library Includes

// Local Includes
#include "packets.h"
#include "therakman.h"

// This Includes
#include "networkplayer.h"

// Static Variables

// Static function prototypes

// Implementation

NetworkPlayer::NetworkPlayer()
{
}

NetworkPlayer::~NetworkPlayer()
{
}

void NetworkPlayer::StoreOldData()
{
	m_oldData = m_playerData;
}

void NetworkPlayer::SendNewData()
{
	if( m_oldData.x != m_playerData.x || m_oldData.y != m_playerData.y )
	{
		SendPositionPacket();
	}

	if( m_oldData.heartID != m_playerData.heartID )
	{
		SendHeartPacket();
	}
}

void NetworkPlayer::SendHeartPacket()
{
}

void NetworkPlayer::SendPositionPacket()
{
}

void 
NetworkPlayer::SendConnectionPacket()
{
	TPlayerConnect packet;
	packet.hairID = m_playerData.hairID;
	packet.headID = m_playerData.headID;
	packet.bodyID = m_playerData.bodyID;
	packet.heartID = m_playerData.heartID;
	packet.playerID = 0;

	TheRakMan::Get().SendPacket( (const char*)&packet, sizeof(packet) );
}