//
//  Atrium
//  Gareth Falkingham
//
//  2013(c) - GNU GPL V3
//
//  File Name   :   heart.h
//  Description :   Class to hold information about a heart. Linked to all entities.
//  Author      :   Gareth Falkingham
//

#pragma once

#if !defined(__ATRIUM_GJ_HEART_H__)
#define __ATRIUM_GJ_HEART_H__

// Library Includes
#include <SFML/Graphics.hpp>

// Local Includes

// Types

// Constants
// Hearts range from 0 - 9 (10 hearts, 5 pairs) (0&1, 2&3)
// A matching heart = if (odd) -1, else +1;
static const int MAX_HEARTS = 10;	

// Prototypes


class Heart
{
// Member Functions
public:
	Heart();
	~Heart();

	void generateHeart();
	int getHeartID();

	bool Initialise(signed int heartID =-1);

	void SetPlayerPosition( const float  _x, const float  _y );
	static bool IsHeartMatch( const unsigned int _yourHeartID, const unsigned int _otherHeart );
	void Process( const float _fDT );
	void Draw( sf::RenderWindow* _window );
	static sf::Texture* sm_pTexture;

protected:

private:

// Member Variables
public:

protected:

private:

	
	sf::Sprite* m_pSprite;
	int m_heartID;

	float m_fPlayerX;
	float m_fPlayerY;
};

#endif // __ATRIUM_GJ_HEART_H__
