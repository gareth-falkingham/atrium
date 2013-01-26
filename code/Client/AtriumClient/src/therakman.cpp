//
//  Atrium
//  Ben Maher
//
//  2013(c) - GNU GPL V3
//
//  File Name   :   therakman.cpp
//  Description :   The Raknet manager, responsible for receiving and sending packets
//  Author      :   Ben Maher
// 

// Library Includes
#include "RakPeerInterface.h"
#include "MessageIdentifiers.h"
#include "RakNetTypes.h"
#include "player.hpp"
#include <string>

// Local Includes
#include "debug.hpp"

// This Includes
#include "therakman.h"

// Static Variables

// Static function prototypes

// Implementation
TheRakMan* TheRakMan::m_RakMan = 0;
using namespace RakNet;

TheRakMan::TheRakMan()
: m_bEstablishedConnection( false )
{
	m_hostAddress = new RakNet::SystemAddress( "192.168.1.70", 7001 );
}

TheRakMan::~TheRakMan()
{
	delete m_hostAddress;
}

TheRakMan& TheRakMan::Get()
{
	if( m_RakMan == 0 )
	{ 
		m_RakMan = new TheRakMan;
		m_RakMan->Initialise();
	}

	return *m_RakMan;
}

void TheRakMan::Destroy()
{
	delete m_RakMan;
	m_RakMan = 0;
}

bool TheRakMan::Initialise()
{
	bool bSuccess = false;

	m_pRakInterface = RakNet::RakPeerInterface::GetInstance();
	RakNet::StartupResult startRes = m_pRakInterface->Startup(1, &RakNet::SocketDescriptor(), 1 );
	if( startRes == RakNet::RAKNET_STARTED )
	{
		bSuccess = true;
		RakNet::ConnectionAttemptResult conRes = m_pRakInterface->Connect( "192.168.1.70", 7001, "MiniTaurus", strlen("MiniTaurus") );
	}

	return bSuccess;
}

void TheRakMan::Update( const float _kfdt ) 
{
	RakNet::Packet *packet;
	for (packet=m_pRakInterface->Receive(); packet; m_pRakInterface->DeallocatePacket(packet), packet=m_pRakInterface->Receive())
		{
			switch (packet->data[0])
				{
				case ID_CONNECTION_REQUEST_ACCEPTED:
					printf("Our connection request has been accepted. Sending Connection Packet.\n");
					m_bEstablishedConnection = true;
					m_pPrimaryPlayer->SendConnectionPacket();
					break;					
				default:
					printf("Message with identifier %i has arrived.\n", packet->data[0]);
					break;
				}
		}
}

void TheRakMan::SendPacket( const char* _pcData, const unsigned int _uLength )
{
	m_pRakInterface->Send(_pcData, _uLength, HIGH_PRIORITY, RELIABLE, 0, *m_hostAddress, true);
}