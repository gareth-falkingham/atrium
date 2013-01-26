//
//  Atrium
//  Ben Maher
//
//  2013(c) - GNU GPL V3
//
//  File Name   :   networkplayer.h
//  Description :   A networked player object.
//  Author      :   Ben Maher
//

#pragma once

#if !defined(__ATRIUM_GJ_NETWORKPLAYER_H__)
#define __ATRIUM_GJ_NETWORKPLAYER_H__

// Library Includes
#include "packets.h"
#include "networkdata.h"

// Local Includes

// Types

// Constants

// Prototypes

class NetworkPlayer
{	
// Member Functions
public:
	NetworkPlayer();
	~NetworkPlayer();

	void StoreOldData();
	void SendNewData();
	
	TNetworkData& GetPlayerData()
	{
		return m_playerData;
	}

	void SendConnectionPacket();
	void SendDisconnectPacket();
	void SendPositionPacket();
	void SendInteractionPacket();
	void SendHeartPacket();

	void ReceiveConnectionPacket(TPlayerConnect& _packet);
	void ReceivePositionPacket(TPlayerUpdateMovement& _packet );
	void ReceiveHeartPacket(TPlayerUpdateHeart& _packet );
	void ReceiveInteractionPacket(TPlayerUpdateInteract& _packet );
	
protected:

private:

// Member Variables
public:

protected:
	TNetworkData m_playerData;
	TNetworkData m_oldData;
private:
};

#endif // __ATRIUM_GJ_NETWORKPLAYER_H__
