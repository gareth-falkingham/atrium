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

// Local Includes

// Types

// Constants

// Prototypes
namespace RakNet
{
	class RakPeerInterface;
};

class TheRakMan
{	
// Member Functions
public:
	TheRakMan();
	~TheRakMan();

	static const TheRakMan& Get();
	static void Destroy();

	const void Update( const float _kfdt ) const;

	void SendPacket();

	bool Initialise();

protected:

private:

// Member Variables
public:

protected:

private:

	static TheRakMan* m_RakMan;
	RakNet::RakPeerInterface* m_pRakInterface;

};

#endif // __ATRIUM_GJ_THERAKMAN_H__
