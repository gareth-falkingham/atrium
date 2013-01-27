//
//  Atrium
//  Gareth Falkingham
//
//  2013(c) - GNU GPL V3
//
//  File Name   :   aiplayer.h
//  Description :   Player that you can interact with, but only you can see. To populate the world when the server is lacking in players.
//  Author      :   Gareth Falkingham
//

#pragma once

#if !defined(__ATRIUM_GJ_AIPLAYER_H__)
#define __ATRIUM_GJ_AIPLAYER_H__

#include "player.hpp"

// Library Includes

// Local Includes

// Types

// Constants

// Prototypes

class AIPlayer : public Player
{	
// Member Functions
public:
	AIPlayer();
	virtual ~AIPlayer();

	virtual void update(float p_delta);

protected:

private:

// Member Variables
public:

protected:

private:

};

#endif // __ATRIUM_GJ_AIPLAYER_H__
