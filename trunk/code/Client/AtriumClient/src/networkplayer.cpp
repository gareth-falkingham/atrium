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

	if( m_oldData.isInteracting != m_playerData.isInteracting )
	{
		SendInteractionPacket();
	}
}

void NetworkPlayer::SendHeartPacket()
{
	TPlayerUpdateHeart packet;
	packet.packetType = PLAYER_HEART;
	packet.playerID = m_playerData.playerID;
	packet.heartID = m_playerData.heartID;

	TheRakMan::Get().SendPacket( (const char*)&packet, sizeof(packet) );
}

void NetworkPlayer::SendPositionPacket()
{
	TPlayerUpdateMovement packet;
	packet.packetType = PLAYER_MOVEMENT;
	packet.playerID = m_playerData.playerID;
	packet.x = m_playerData.x;
	packet.y = m_playerData.y;

	TheRakMan::Get().SendPacket( (const char*)&packet, sizeof(packet) );
}

void NetworkPlayer::SendInteractionPacket()
{
	TPlayerUpdateInteract packet;
	packet.packetType = PLAYER_INTERACT;
	packet.playerID = m_playerData.playerID;
	packet.isInteracting = m_playerData.isInteracting;

	TheRakMan::Get().SendPacket( (const char*)&packet, sizeof(packet) );
}

void 
NetworkPlayer::SendConnectionPacket()
{
	TPlayerConnect packet;
	packet.packetType = PLAYER_CONNECT;
	packet.hairID = m_playerData.hairID;
	packet.headID = m_playerData.headID;
	packet.bodyID = m_playerData.bodyID;
	packet.heartID = m_playerData.heartID;
	packet.playerID = 0; //WE DO NOT HAVE A PLAYER ID YET.

	//Send x and y.

	TheRakMan::Get().SendPacket( (const char*)&packet, sizeof(packet) );
}

void 
NetworkPlayer::ReceiveConnectionPacket(TPlayerConnect& _packet)
{
	m_playerData.playerID = _packet.playerID;

	//Receive x and y.
	m_playerData.x = 0;
	m_playerData.y = 0;
	m_playerData.bodyID = _packet.bodyID;
	m_playerData.headID = _packet.headID;
	m_playerData.hairID = _packet.bodyID;
	m_playerData.heartID = _packet.heartID;
	m_playerData.isInteracting = false;
}

void
NetworkPlayer::ReceivePositionPacket(TPlayerUpdateMovement& _packet )
{
	m_playerData.x = _packet.x;
	m_playerData.y = _packet.y;
}

void 
NetworkPlayer::ReceiveHeartPacket(TPlayerUpdateHeart& _packet )
{
	m_playerData.heartID = _packet.heartID;
}

void 
NetworkPlayer::ReceiveInteractionPacket(TPlayerUpdateInteract& _packet )
{
	m_playerData.isInteracting = _packet.isInteracting;
}