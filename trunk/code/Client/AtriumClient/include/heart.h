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

// Local Includes

// Types

// Constants
// Hearts range from 0 - 9 (10 hearts, 5 pairs) (0&1, 2&3)
// A matching heart = if (odd) -1, else +1;
static const int MAX_HEARTS = 9;	

// Prototypes


class Heart
{
// Member Functions
public:
	Heart();
	~Heart();

	void generateHeart();
	int getHeartID();

protected:

private:

// Member Variables
public:

protected:

private:
	int m_heartID;

};

#endif // __ATRIUM_GJ_HEART_H__
