#include "Atrium.h"
#include <iostream>
#include <string>
#include "packets.h"

using namespace RakNet;

// Constructor
Atrium::Atrium()
	:m_nextUserID(0)
{
	m_pRakPeerInterface = RakPeerInterface::GetInstance();

	StartupResult success = m_pRakPeerInterface->Startup(110, &SocketDescriptor(7001, 0), 1);
	
	if (success != StartupResult::RAKNET_STARTED)
	{
		std::cout << "Failed to start RakNet service.";
	}
	else
	{
		m_pRakPeerInterface->SetMaximumIncomingConnections(100);
		m_pRakPeerInterface->SetIncomingPassword("MiniTaurus", 10);
	}
}

// Destructor
Atrium::~Atrium()
{
	RakPeerInterface::DestroyInstance(m_pRakPeerInterface);
	m_pRakPeerInterface = 0;
}

void Atrium::process()
{
	bool isQuitting = false;
	std::string input = "";
	
	while (!isQuitting)
	{
		// Do stuff
		processPackets();

		// Check input, if exit/quit then change bool
		std::cin >>input;

		if (input == "exit")
		{
			isQuitting = true;
			std::cout << "Exiting...";
		}

		// Let OS process stuff
		Sleep(0);
	}
}

void Atrium::processPackets()
{
	Packet* packet = 0;

	do
	{
		packet = m_pRakPeerInterface->Receive();

		if (packet != 0)
		{
			// Process
			std::cout << packet->systemAddress.ToString();

			EPacketTypes packetType = static_cast<EPacketTypes>(packet->data[0]);
		}
	}
	while (packet != 0);
}
