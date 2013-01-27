#ifndef PLAYER_HPP
#define PLAYER_HPP

#pragma once

#include <string>
#include <sstream>
#include <ostream>
#include <iomanip>
#include <cmath>

#include "const.hpp"
#include "assets.hpp"
#include "world_entity.hpp"
#include "networkplayer.h"
#include "animated_sprite.h"
#include "heart.h"

enum Direction { LEFT, RIGHT, UP, NONE };
enum PlayerState { STANDING, WALKING, JUMPING };

class Player : public WorldEntity, public NetworkPlayer{
	private:

		Heart m_heart;
		PlayerState m_playerState;
		float m_showHeartTimer;
		//float m_localX;
		//float m_localY;
		AnimatedSprite* m_animatedSprite;
		std::string buildAssetPath(std::string type, int p_ext);

		static float sm_playerLocalX;
		static float sm_playerWorldX;
	
	protected:
		Direction m_facing;	
		float m_speed;

		void regenCharacter();	// Dispose current images, create new body/head/hair combo, re-create sprites


	public:
	
		Player();
		Player(int p_head, int p_hair, int p_body, int p_heart);
		virtual ~Player();
		
		void randomiseBody();
		void initializeSprite(int p_body, int p_head, int p_hair);

		virtual void ReceiveHeartPacket(TPlayerUpdateHeart& _packet);

		virtual void UpdatePosition();
		void moveLeft(float fDT);
		void moveRight(float fDT);
		void moveNone(float fDT);
		void jump();
		
		void generateHeart(int heartID = -1);

		virtual float GetXPosition(){ return m_playerData.x; }
		virtual unsigned int GetHeartID(){ return m_playerData.heartID; }

		float speed();

		virtual void update(float p_delta);
		virtual void render(sf::RenderWindow* p_window);

};

#endif