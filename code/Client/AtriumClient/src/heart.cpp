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

// Implementation

Heart::Heart()
{
}

Heart::~Heart()
{
}

void Heart::generateHeart()
{
	m_heartID = (rand() % MAX_HEARTS) + 1;
	std::cout << "Heart Generated for the player! : " << m_heartID << std::endl;
}

int Heart::getHeartID()
{
	return m_heartID;
}