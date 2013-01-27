//
//  Atrium
//  Gareth Falkingham
//
//  2013(c) - GNU GPL V3
//
//  File Name   :   heart.cpp
//  Description :   Class to hold information about a heart. Linked to all entities.
//  Author      :   Gareth Falkingham
// 

// Library Includes

// Local Includes

// This Includes
#include <cstdlib>
#include <iostream>
#include "heart.h"

// Static Variables

// Static function prototypes
sf::Texture* Heart::sm_pTexture= 0;

// Implementation

Heart::Heart()
: m_pSprite ( 0 )
{
}

Heart::~Heart()
{
	delete m_pSprite;
	m_pSprite = 0;
}

void Heart::generateHeart()
{
	m_heartID = (rand() % MAX_HEARTS);
	std::cout << "Heart Generated for the player! : " << m_heartID << std::endl;
}

int Heart::getHeartID()
{
	return m_heartID;
}

bool Heart::Initialise( signed int heartID )
{
	if( heartID == -1 )
	{
		generateHeart();
	}
	else
	{
		m_heartID = heartID;
	}

	if( sm_pTexture == 0 )
	{
		sm_pTexture = new sf::Texture;
		sm_pTexture->loadFromFile("assets/images/hearts.png");
	}

	if( m_pSprite == 0 )
	{
		m_pSprite = new sf::Sprite;
		m_pSprite->setTexture( *sm_pTexture );
	}

	return true; //Fuck da police.
}

void 
Heart::SetPlayerPosition( const float  _x, const float  _y )
{
	m_fPlayerX = _x;
	m_fPlayerY = _y;
}
	
void Heart::Process( const float _fDT )
{
}

bool Heart::IsHeartMatch( const unsigned int _yourHeartID, const unsigned int _otherHeart )
{
	if( _yourHeartID %2 == 0 )
	{
		//Even. The matching heart must be this one + 1.
		return (_yourHeartID + 1) == _otherHeart;
	}
	else
	{
		//Odd. The matching heart must be this one - 1.
		return (_yourHeartID - 1) == _otherHeart;
	}
}

void Heart::Draw( sf::RenderWindow* _window )
{
	//Location of heart in the image.
	int heartRow	= m_heartID / 2;
	int heartColumn = m_heartID % 2;
	
	//Create Rect.
	sf::IntRect rect;
	rect.left	= heartColumn*64;
	rect.top	= heartRow*64;
	rect.width	= 64;
	rect.height	= 64;

	//Draw.
	m_pSprite->setTextureRect( rect );
	m_pSprite->setPosition( m_fPlayerX-32, m_fPlayerY-80 );
	_window->draw( *m_pSprite );
}