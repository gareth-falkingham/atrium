//
//  Atrium
//  Gareth Falkingham
//
//  2013(c) - GNU GPL V3
//
//  File Name   :   aiplayer.cpp
//  Description :   Player that you can interact with, but only you can see. To populate the world when the server is lacking in players.
//  Author      :   Gareth Falkingham
// 

// Library Includes

// Local Includes

// This Includes
#include "aiplayer.h"

// Static Variables

// Static function prototypes

// Implementation

AIPlayer::AIPlayer()
{
	m_speed = 0.02f;

	int random = rand() % 2;
	m_facing = static_cast<Direction>(random);
}

AIPlayer::~AIPlayer()
{

}

void AIPlayer::update(float p_delta)
{
	// Update AI position
	if (m_facing == LEFT)
	{
		moveLeft(0.01f);

		if (m_playerData.x <= -20.0f)
		{
			//m_facing = RIGHT;
			regenCharacter();
			moveRight(0.01f);
		}
	}
	else if (m_facing == RIGHT)
	{
		moveRight(0.01f);

		if (m_playerData.x >= 820.0f)
		{
			//m_facing = LEFT;
			regenCharacter();
			moveLeft(0.01f);
		}
	}
	else
	{
		moveNone(0.01f);
	}


	Player::update(p_delta);
}