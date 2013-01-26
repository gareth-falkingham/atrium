//
//  Atrium
//  Gareth Falkingham
//
//  2013(c) - GNU GPL V3
//
//  File Name   :   soundmanager.cpp
//  Description :   Class to hold references to sounds.
//  Author      :   Gareth Falkingham
// 

// Library Includes

// Local Includes

// This Includes
#include "soundmanager.h"

// Static Variables
SoundManager* SoundManager::s_instance = 0;

// Static function prototypes
SoundManager& SoundManager::getInstance()
{
	if (s_instance == 0)
	{
		s_instance = new SoundManager();
	}
	return *s_instance;
}

void SoundManager::destroy()
{
	if (s_instance != 0)
	{
		delete s_instance;
		s_instance = 0;
	}
}

// Implementation

SoundManager::SoundManager()
{

}

SoundManager::~SoundManager()
{
	SoundMap::iterator iter1;
	SoundBufferMap::iterator iter2;

	//Delete Sounds
	//for( iter1 = m_soundMap.begin() ; iter1 != m_soundMap.end() ; ++iter1 )
	//{
	//	iter1->second->stop();
	//	delete iter1->second;
	//	iter1->second = 0;
	//}

	////Delete Buffers.
	//for( iter2 = m_soundBufferMap.begin() ; iter2 != m_soundBufferMap.end() ; ++iter2 )
	//{
	//	delete iter2->second;
	//	iter2->second = 0;
	//}

	m_soundMap.clear();
	m_soundBufferMap.clear();
}

void SoundManager::initialise()
{

}

void SoundManager::playSound(ESounds _sound)
{
	//SoundMap::iterator it = m_soundMap.find(_sound);

	//if (it != m_soundMap.end())
	//{
	//	// Valid sound, is in map
	//	it->second->play();
	//}
	//else
	//{
	//	m_buff.loadFromFile( "assets/sounds/Test.wav" );
	//	m_sound.setBuffer(m_buff);
	//	m_sound.play();

	//	// Create sound, then play
	//	SoundBuffer* buffer = new SoundBuffer();
	//	if (buffer->loadFromFile("assets/sounds/Test.wav"))
	//	{
	//		Sound* sound = new Sound;
	//		sound->setBuffer( *buffer );

	//		m_soundBufferMap[_sound] = buffer;
	//		m_soundMap[_sound] = sound;

	//		sound->play();
	//		//sound = 0;
	//	}
	//	else
	//	{
	//		delete buffer;
	//	}

	//	//buffer = 0;
	//}
}

void SoundManager::stopSound(ESounds _sound)
{
	SoundMap::iterator it = m_soundMap.find(_sound);

	if (it != m_soundMap.end())
	{
		// Sound exists, stop it
		it->second->stop();
	}
}
