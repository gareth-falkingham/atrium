#ifndef GGJ2013_ATRIUM
#define GGJ2013_ATRIUM

#include "RakPeer.h"
#include "User.h"
#include "packets.h"
#include "MessageIdentifiers.h"
#include <unordered_map>

typedef std::unordered_map <int, User*> UserMap;

class Atrium
{
public:
	Atrium();
	~Atrium();

	void process();

private:
	RakNet::RakPeerInterface* m_pRakPeerInterface;
	UserMap m_pUserMap;
	unsigned short m_nextUserID;

	void processPackets();

	void clientDisconnectUser(RakNet::Packet _packet);
	void disconnectUser(RakNet::Packet _packet);
	void connectUser(RakNet::Packet _packet);
	void playerInteract(RakNet::Packet _packet);
	void playerMove(RakNet::Packet _packet);
	void onPlayerHeart(RakNet::Packet _packet);
	void broadcastToClients(const char* _data, int _size, RakNet::AddressOrGUID exclude = RakNet::UNASSIGNED_RAKNET_GUID);

	User* createNewUser(RakNet::Packet _packet);

};

#endif