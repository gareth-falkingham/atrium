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
#include "networkdata.h"

// Local Includes

// Types

// Constants

// Prototypes
class TheRakMan;

class NetworkPlayer
{	
// Member Functions
public:
	NetworkPlayer();
	~NetworkPlayer();

	void StoreOldData();
	void SendNewData();

	void SendConnectionPacket();
	void SendPositionPacket();
	void SendInteractionPacket();
	void SendHeartPacket();
	
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
