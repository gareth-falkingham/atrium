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
#include <iostream>

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
	
	/*std::cout << "Constructed Sync Packet:" << std::endl;
	std::cout << "Body : " << static_cast<unsigned int>(syncPacket.bodyID) << std::endl;
	std::cout << "Head : " << static_cast<unsigned int>(syncPacket.headID) << std::endl;
	std::cout << "Hair : " << static_cast<unsigned int>(syncPacket.hairID) << std::endl;
	std::cout << "Heart : " << static_cast<unsigned int>(syncPacket.heartID) << std::endl;*/

	return syncPacket;
}

