//
//  Atrium
//  Gareth Falkingham
//
//  2013(c) - GNU GPL V3
//
//  File Name   :   user.h
//  Description :   User
//  Author      :   Gareth Falkingham
//

#ifndef __ATRIUM_GJ_USER_H__
#define __ATRIUM_GJ_USER_H__

#include "RakPeer.h"
#include "packets.h"

class User
{	
// Member Functions
public:
	User();
	~User();

	TPlayerConnect getSyncPacket();

protected:

private:

// Member Variables
public:
	RakNet::SystemAddress clientAddress;

	unsigned short playerID;		//Id of the player.
	unsigned char hairID;			//Id of the player's hair.
	unsigned char headID;			//Id of the player's head.
	unsigned char bodyID;			//Id of the player's body.
	unsigned char heartID;			//Id of the player's heart.

	float x;						//X Position of the player.
	float y;						//Y Position of the player.

	unsigned char isInteracting;	//Will be "1" if a player is interacting, or "0" if the player is not.

protected:

private:

};

#endif // __ATRIUM_GJ_USER_H__
