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
#include "world.hpp"

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
	m_hostAddress = new RakNet::SystemAddress( "23.22.88.17", 7001 );
}

TheRakMan::~TheRakMan()
{
	delete m_hostAddress;

	std::map<unsigned short, Player*>::iterator iter;
	for( iter = m_mapPPlayers.begin() ; iter != m_mapPPlayers.end() ; ++iter )
	{
		if( m_pPrimaryPlayer->GetPlayerData().playerID != iter->first )
		{
			delete iter->second;
			iter->second = 0;
		}
	}

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
		RakNet::ConnectionAttemptResult conRes = m_pRakInterface->Connect(m_hostAddress->ToString(false), m_hostAddress->GetPort(), "MiniTaurus", strlen("MiniTaurus") );

		std::cout << conRes << std::endl;
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
			{
				printf("Our connection request has been accepted. Sending Connection Packet.\n");
				m_pPrimaryPlayer->SendConnectionPacket();
				break;					
			}
		case PLAYER_CONNECT:
			{
				TPlayerConnect pC;
				memcpy(&pC, packet->data, sizeof( pC ) );

				//Doth another player of equitable description exist?
				if( m_mapPPlayers.find(pC.playerID) == m_mapPPlayers.end() )
				{
					if( IsPrimaryPlayer(pC.playerID) == false )
					{
						//Create new player.
						Player* tempPlayer = new Player();
						tempPlayer->ReceiveConnectionPacket( pC );
						m_mapPPlayers[pC.playerID] = tempPlayer;
						m_pWorld->addEntity(m_mapPPlayers[pC.playerID]);
						printf("Received a new connection and dealt with it successfully.\n");
					}
					else
					{
						printf("Received a new connection for... Myself?" );
					}
				}
				else
				{
					printf("Received a player connect message for a player that already exists.\n");
				}

				break;
			}
		case PLAYER_DISCONNECT:
			{
				TPlayerDisconnect pDC;
				memcpy( &pDC, packet->data, sizeof( pDC ) );

				//Iterate through map, find this player and destroy them.
				std::map<unsigned short, Player*>::iterator iter = m_mapPPlayers.find( pDC.playerID );
				if( iter != m_mapPPlayers.end() )
				{
					//Remove from update list.
					m_pWorld->removeEntity( iter->second );

					//Destroy this player and delete it.
					delete iter->second;
					iter->second = 0;
					m_mapPPlayers.erase(iter);
					printf("Received a player disconnect message and dealt with it successfully.\n");
				}
				else
				{
					printf("Received a player disconnect message for a player that doesn't exist.\n");
				}
				break;
			}
		case PLAYER_ID:
			{
				TPlayerID playerIDPack;
				memcpy( &playerIDPack, packet->data, sizeof( playerIDPack ) );

				printf("Received our player ID message. Player id is: %i\n", playerIDPack.playerID );
				
				m_pPrimaryPlayer->GetPlayerData().playerID = playerIDPack.playerID;
				m_bEstablishedConnection = true;
				break;
			}
		case PLAYER_MOVEMENT:
			{
				TPlayerUpdateMovement movePack;
				memcpy( &movePack, packet->data, sizeof( movePack ) );

				//Iterate through map, find this player and call ReceivePositionPacket.
				std::map<unsigned short, Player*>::iterator iter = m_mapPPlayers.find( movePack.playerID );
				if( iter != m_mapPPlayers.end() )
				{
					iter->second->ReceivePositionPacket( movePack );
					printf("Received a player movement message for player: %i\n", movePack.playerID);
				}
				else
				{
					printf("Received a player movement message for a player that doesn't exist: %i\n", movePack.playerID);
				}
				break;
			}
		case PLAYER_INTERACT:
			{
				TPlayerUpdateInteract interactPacket;
				memcpy( &interactPacket, packet->data, sizeof( TPlayerUpdateInteract ) );

				//Iterate through map, find this player and call ReceiveInteractionPacket.
				std::map<unsigned short, Player*>::iterator iter = m_mapPPlayers.find( interactPacket.playerID );
				if( iter != m_mapPPlayers.end() )
				{
					iter->second->ReceiveInteractionPacket( interactPacket );
					printf("Received a player interaction message for player: %i\n", interactPacket.playerID);
				}
				else
				{
					printf("Received a player interaction message for a player that doesn't exist.\n");
				}
				break;
			}
		case PLAYER_HEART:
			{
				TPlayerUpdateHeart heartPacket;
				memcpy( &heartPacket, packet->data, sizeof( heartPacket ) );

				//Iterate through map, find this player and call ReceiveHeartPacket.
				std::map<unsigned short, Player*>::iterator iter = m_mapPPlayers.find( heartPacket.playerID );
				if( iter != m_mapPPlayers.end() )
				{
					iter->second->ReceiveHeartPacket( heartPacket );
					printf("Received a player heart message for player: %i\n", heartPacket.playerID);
				}
				else
				{
					printf("Received a player heart message for a player that doesn't exist.\n");
				}
				break;
			}
		default:
			{
				printf("Message with identifier %i has arrived.\n", packet->data[0]);
				break;
			}
		}
	}
}

void TheRakMan::SendPacket( const char* _pcData, const unsigned int _uLength, bool _sendImmediate )
{
	PacketPriority priority = HIGH_PRIORITY;
	if( _sendImmediate == true )
	{
		priority = IMMEDIATE_PRIORITY;
	}

	if( m_pRakInterface->Send(_pcData, _uLength, priority, RELIABLE, 0, *m_hostAddress, false) == 0)
	{
		Debug::log( EXCEPTION, "TheRakMan::SendPacket", "Sending failed" );
	}
}

bool 
TheRakMan::IsPrimaryPlayer( unsigned short _yourID )
{
	return _yourID == m_pPrimaryPlayer->GetPlayerData().playerID;
}