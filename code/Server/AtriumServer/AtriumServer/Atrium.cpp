#include "Atrium.h"
#include <iostream>
#include <string>

using namespace RakNet;

// Constructor
Atrium::Atrium()
	:m_nextUserID(0)
{
	int port = 7001;

	m_pRakPeerInterface = RakPeerInterface::GetInstance();

	StartupResult success = m_pRakPeerInterface->Startup(110, &SocketDescriptor(port, 0), 1);
	
	if (success != StartupResult::RAKNET_STARTED)
	{
		std::cout << "Failed to start RakNet service." << std::endl;
	}
	else
	{
		m_pRakPeerInterface->SetMaximumIncomingConnections(100);
		m_pRakPeerInterface->SetIncomingPassword("MiniTaurus", 10);
		std::cout << "RakNet service started - listening on port " << port << std::endl;
	}
}

// Destructor
Atrium::~Atrium()
{
	for (UserMap::iterator iterator = m_pUserMap.begin(); iterator != m_pUserMap.end(); ++iterator)
	{
		delete iterator->second;
		iterator->second = 0;
	}

	m_pUserMap.clear();

	RakPeerInterface::DestroyInstance(m_pRakPeerInterface);
	m_pRakPeerInterface = 0;
}

// Heh.
bool isTerminating;

bool ctrlHandler(DWORD ctrlType)
{
	std::cout << "Caught Ctrl!!" << std::endl;
	isTerminating = true;
	return true;
}

void Atrium::process()
{
	isTerminating = false;
	std::string input = "";
	
	SetConsoleCtrlHandler((PHANDLER_ROUTINE)ctrlHandler, true);

	while (!isTerminating)
	{
		// Do stuff
		processPackets();

		// Let OS process stuff
		Sleep(0);
	}
}

void Atrium::processPackets()
{
	Packet* packet = 0;
	unsigned char packetType;

	do
	{
		packet = m_pRakPeerInterface->Receive();

		if (packet != 0)
		{
			// Process
			std::cout << packet->systemAddress.ToString() << std::endl;

			packetType = (unsigned char)packet->data[0];
			
			switch (packetType)
			{
			case ID_CONNECTION_LOST:
			case ID_DISCONNECTION_NOTIFICATION:
				// User disconnected from internet drop
				disconnectUser(*packet);
				break;

			case PLAYER_CONNECT:
				// Client request
				connectUser(*packet);
				break;

			case PLAYER_DISCONNECT:
				// Client chose to disconnect
				clientDisconnectUser(*packet);
				break;

			case PLAYER_INTERACT:
				playerInteract(*packet);
				break;

			case PLAYER_MOVEMENT:
				playerMove(*packet);
				break;

			default:
				// Nothing
				std::cout << "Packet is not recognised - " << static_cast<unsigned int>(packetType) << std::endl;
				break;
			}

			m_pRakPeerInterface->DeallocatePacket(packet);
		}
	} 
	while (packet != 0);
}

void Atrium::clientDisconnectUser(Packet _packet)
{
	TPlayerDisconnect convertedPacket;
	memcpy_s(&convertedPacket, sizeof(TPlayerDisconnect), _packet.data, sizeof(TPlayerDisconnect));
	
	// Delete user from map (based on id)
	User* oldUser = m_pUserMap[convertedPacket.playerID];
	m_pUserMap.erase(convertedPacket.playerID);

	delete oldUser;
	oldUser = 0;

	// Inform clients of the disconnect
	broadcastToClients(reinterpret_cast<char*>(_packet.data), sizeof(TPlayerDisconnect));
}

void Atrium::disconnectUser(Packet _packet)
{
	User* oldUser = 0;
	bool isFound = false;

	// Delete user from map (based on ip/port)
	for (UserMap::iterator iterator = m_pUserMap.begin(); iterator != m_pUserMap.end(); ++iterator)
	{
		oldUser = iterator->second;
		if (oldUser->clientAddress == _packet.systemAddress)
		{
			std::cout << "Client disconnected remotely: " << _packet.systemAddress.ToString() << std::endl;
			m_pUserMap.erase(iterator);
			isFound = true;
			break;
		}
	}

	if (isFound)
	{
		// Inform clients of the disconnect
		TPlayerDisconnect convertedPacket;
		convertedPacket.packetType = EPacketTypes::PLAYER_DISCONNECT;
		convertedPacket.playerID = oldUser->playerID;

		//const char* broadcastPacket;
		//memcpy_s(&broadcastPacket, sizeof(TPlayerDisconnect), &convertedPacket, sizeof(TPlayerDisconnect));
		
		broadcastToClients((const char*)&convertedPacket, sizeof(TPlayerDisconnect));
		delete oldUser;
		oldUser = 0;
	}
}

void Atrium::connectUser(Packet _packet)
{
	// Create a new user
	User* newUser = createNewUser(_packet);
	m_pUserMap[newUser->playerID] = newUser;

	// Copy data from client into a struct
	TPlayerConnect playerData;
	memcpy_s(&playerData, sizeof(TPlayerConnect), _packet.data, sizeof(TPlayerConnect));
	playerData.playerID = newUser->playerID;
	
	// Create packet to inform user of their ID
	TPlayerID playerIDPacket;
	playerIDPacket.packetType = EPacketTypes::PLAYER_ID;
	playerIDPacket.playerID = newUser->playerID;
	const char* connectPacket = reinterpret_cast<const char*>(&playerIDPacket);

	// Tell player their ID
	m_pRakPeerInterface->Send(connectPacket, sizeof(TPlayerID), PacketPriority::IMMEDIATE_PRIORITY, PacketReliability::RELIABLE, 0, newUser->clientAddress, false);

	// Inform every client that a new player has joined
	broadcastToClients(connectPacket, sizeof(TPlayerConnect), _packet.systemAddress);

	// Inform the user of the curent state of things
	User* otherUser = 0;
	TPlayerConnect syncData;

	// Delete user from map (based on ip/port)
	for (UserMap::iterator iterator = m_pUserMap.begin(); iterator != m_pUserMap.end(); ++iterator)
	{
		otherUser = iterator->second;
		if (otherUser != newUser)
		{
			// Send all information to the new client
			syncData = otherUser->getSyncPacket();
			connectPacket = reinterpret_cast<const char*>(&syncData);
			m_pRakPeerInterface->Send(connectPacket, sizeof(TPlayerConnect), PacketPriority::HIGH_PRIORITY, PacketReliability::RELIABLE, 0, newUser->clientAddress, false);
			delete connectPacket;
		}
	}

	// Clear vars
	otherUser = 0;
	connectPacket = 0;
	newUser = 0;
}

void Atrium::playerInteract(Packet _packet)
{
	// Update player pointer in map

	// Inform other users of the change
}

void Atrium::playerMove(Packet _packet)
{
	// Update player pointer in map
	TPlayerUpdateMovement convertedPacket;
	memcpy_s(&convertedPacket, sizeof(TPlayerUpdateMovement), _packet.data, sizeof(TPlayerUpdateMovement));

	User* movedUser = m_pUserMap[convertedPacket.playerID];
	movedUser->x = convertedPacket.x;
	movedUser->y = convertedPacket.y;

	// Inform other users of the change
	broadcastToClients((const char*)&convertedPacket, sizeof(TPlayerUpdateMovement), _packet.systemAddress);
}

void Atrium::broadcastToClients(const char* _data, int _size, SystemAddress exclude)
{
	AddressOrGUID excludeAddress;

	if (exclude == 0)
	{
		excludeAddress = UNASSIGNED_RAKNET_GUID;
	}
	else
	{
		excludeAddress = exclude;
	}

	// Send the packet to all clients
	m_pRakPeerInterface->Send(_data, _size, PacketPriority::MEDIUM_PRIORITY, PacketReliability::RELIABLE, 0, excludeAddress, true);
}

User* Atrium::createNewUser(RakNet::Packet _packet)
{
	User* newUser = new User();
	newUser->clientAddress = _packet.systemAddress;
	newUser->playerID = m_nextUserID;
	m_nextUserID++;

	return newUser;
}
