//
//  Atrium
//  Ben Maher
//
//  2013(c) - GNU GPL V3
//
//  File Name   :   therakman.h
//  Description :   The Raknet manager, responsible for receiving and sending packets
//  Author      :   Ben Maher
//

#pragma once

#if !defined(__ATRIUM_GJ_THERAKMAN_H__)
#define __ATRIUM_GJ_THERAKMAN_H__

// Library Includes
#include <string>
#include <map>

// Local Includes

// Types

// Constants

// Prototypes
namespace RakNet
{
	class RakPeerInterface;
	struct SystemAddress;
};
class Player;
class World;

class TheRakMan
{	
// Member Functions
public:
	TheRakMan();
	~TheRakMan();

	static TheRakMan& Get();
	static void Destroy();

	void Update( const float _kfdt );
	void SendPacket( const char* _pcData, const unsigned int _uLength, bool _sendImmediate = false );
	bool IsPrimaryPlayer( unsigned short _yourID );

	//void SendPacket();

	bool Initialise();

protected:

private:

// Member Variables
public:

	bool m_bEstablishedConnection;
	Player* m_pPrimaryPlayer;
	World* m_pWorld;

protected:

private:

	static TheRakMan* m_RakMan;
	RakNet::RakPeerInterface* m_pRakInterface;
	RakNet::SystemAddress* m_hostAddress;

	std::map<unsigned short, Player*> m_mapPPlayers;

	std::string m_strHostAddress;

	
};

#endif // __ATRIUM_GJ_THERAKMAN_H__
