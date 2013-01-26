//
//  Atrium
//  Gareth Falkingham
//
//  2013(c) - GNU GPL V3
//
//  File Name   :   user.cpp
//  Description :   User
//  Author      :   Gareth Falkingham
// 

// Library Includes

// Local Includes

// This Includes
#include "User.h"
#include "packets.h"

// Static Variables

// Static function prototypes

// Implementation

User::User()
{
}

User::~User()
{
}

TPlayerConnect User::getSyncPacket()
{
	TPlayerConnect syncPacket;

	syncPacket.bodyID = bodyID;
	syncPacket.hairID = hairID;
	syncPacket.headID = headID;
	syncPacket.heartID = heartID;

	syncPacket.x = x;
	syncPacket.y = y;

	syncPacket.playerID = playerID;
	syncPacket.packetType = PLAYER_CONNECT;
	syncPacket.isInteracting = isInteracting;

	return syncPacket;
}

