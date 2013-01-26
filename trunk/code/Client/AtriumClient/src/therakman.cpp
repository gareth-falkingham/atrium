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
{
}

TheRakMan::~TheRakMan()
{
}

const TheRakMan& TheRakMan::Get()
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

	std::string strHostAddress = "192.168.1.70";

	m_pRakInterface = RakNet::RakPeerInterface::GetInstance();
	RakNet::StartupResult startRes = m_pRakInterface->Startup(1, &RakNet::SocketDescriptor(), 1 );
	if( startRes == RakNet::RAKNET_STARTED )
	{
		bSuccess = true;
		RakNet::ConnectionAttemptResult conRes = m_pRakInterface->Connect( strHostAddress.c_str(), 7001, "MiniTaurus", strlen("MiniTaurus") );
	}

	return bSuccess;
}

const void TheRakMan::Update( const float _kfdt ) const
{
	RakNet::Packet *packet;
	for (packet=m_pRakInterface->Receive(); packet; m_pRakInterface->DeallocatePacket(packet), packet=m_pRakInterface->Receive())
		{
			switch (packet->data[0])
				{
				case ID_CONNECTION_REQUEST_ACCEPTED:
					printf("Our connection request has been accepted.\n");
					break;					
				default:
					printf("Message with identifier %i has arrived.\n", packet->data[0]);
					break;
				}
		}
}