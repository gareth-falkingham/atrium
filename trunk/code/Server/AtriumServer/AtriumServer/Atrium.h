#ifndef GGJ2013_ATRIUM
#define GGJ2013_ATRIUM

#include "RakPeer.h"
#include "User.h"
#include <unordered_map>

typedef std::unordered_map <int, User> UserMap;

class Atrium
{
public:
	Atrium();
	~Atrium();

	void process();

private:
	RakNet::RakPeerInterface* m_pRakPeerInterface;
	UserMap m_pUserMap;

	int m_nextUserID;
	void processPackets();

};

#endif