//
//  Atrium
//  Gareth Falkingham
//
//  2013(c) - GNU GPL V3
//
//  File Name   :   soundmanager.h
//  Description :   Class to hold references to sounds.
//  Author      :   Gareth Falkingham
//

#pragma once

#if !defined(__ATRIUM_GJ_SOUNDMANAGER_H__)
#define __ATRIUM_GJ_SOUNDMANAGER_H__

// Library Includes
#include <map>

// Local Includes
#include "SFML\Audio.hpp"

// Types
using namespace sf;

enum ESounds
{
	FOOTSTEPS,
	JUMP,
	LAND
};

typedef std::map <ESounds, Sound*> SoundMap;
typedef std::map <ESounds, SoundBuffer*> SoundBufferMap;

// Constants

// Prototypes

class SoundManager
{	
// Member Functions
public:
	SoundManager();
	~SoundManager();
	
	static SoundManager& getInstance();
	static void destroy();

	void initialise();

	void playSound(ESounds _sound);
	void stopSound(ESounds _sound);

protected:

private:

// Member Variables
public:

protected:

private:
	static SoundManager* s_instance;

	SoundMap m_soundMap;
	SoundBufferMap m_soundBufferMap;

};

#endif // __ATRIUM_GJ_SOUNDMANAGER_H__
