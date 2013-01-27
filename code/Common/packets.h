#ifndef __ATRIUM_PACKETS_H__
#define __ATRIUM_PACKETS_H__

#pragma once

#include "MessageIdentifiers.h"

enum EPacketTypes
{
	PLAYER_CONNECT = ID_USER_PACKET_ENUM,
	PLAYER_DISCONNECT,
	PLAYER_MOVEMENT,
	PLAYER_INTERACT,
	PLAYER_HEART,
	PLAYER_WON,
	PLAYER_ID
};

//Sent when a player connects.
//RELIABLE
struct TPlayerConnect
{
	EPacketTypes packetType;		//Type of the packet.
	unsigned short playerID;		//Id of the player.
	unsigned char hairID;			//Id of the player's hair.
	unsigned char headID;			//Id of the player's head.
	unsigned char bodyID;			//Id of the player's body.
	unsigned char heartID;			//Id of the player's heart.
	float x;						//X Position of the player.
	float y;						//Y Position of the player.
	unsigned char isInteracting;	//Will be "1" if a player is interacting, or "0" if the player is not.
};

//Sent to give the user his/her id
//RELIABLE, HIGH_PRIORITY
struct TPlayerID
{
	EPacketTypes packetType;		//Type of the packet.
	unsigned short playerID;		//Id of the player.
};

//Sent when a player disconnects.
//RELIABLE
struct TPlayerDisconnect
{
	EPacketTypes packetType;		//Type of the packet.
	unsigned short playerID;		//Id of the player.
};

//Sent when a player's position changes.
//UNRELIABLE
struct TPlayerUpdateMovement
{
	EPacketTypes packetType;		//Type of the packet.
	unsigned short playerID;		//Id of the player.
	float x;						//X Position of the player.
	float y;						//Y Position of the player.
};

//Sent when a player's interaction changes.
//RELIABLE
struct TPlayerUpdateInteract
{
	EPacketTypes packetType;		//Type of the packet.
	unsigned short playerID;		//Id of the player.
	unsigned char isInteracting;	//Will be "1" if a player is interacting, or "0" if the player is not.
};

//Sent when a player's heart piece CHANGES.
//RELIABLE
struct TPlayerUpdateHeart
{
	EPacketTypes packetType;		//Type of the packet.
	unsigned short playerID;		//Id of the player.
	unsigned char heartID;			//Id of the player's NEW heart.
};

//PlayerWon.
struct TPlayerWon
{
	EPacketTypes packetType;
	unsigned short playerID;
	unsigned short numMatches;
};

#endif //__ATRIUM_PACKETS_H__