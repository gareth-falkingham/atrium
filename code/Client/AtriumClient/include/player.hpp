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

enum Direction { LEFT, RIGHT, UP, NONE };
enum PlayerState { STANDING, WALKING, JUMPING };

class Player : public WorldEntity, public NetworkPlayer{
	private:

		Direction m_facing;	
		PlayerState m_playerState;
		float m_speed;
		//float m_localX;
		//float m_localY;
		AnimatedSprite* m_animatedSprite;
		std::string buildAssetPath(std::string type, int p_ext);

		static float sm_playerLocalX;
		static float sm_playerWorldX;
		

	public:
	
		Player();
		Player(int p_head, int p_hair, int p_body);
		virtual ~Player();

		void initializeSprite(int p_body, int p_head, int p_hair);
		virtual void UpdatePosition();
		void moveLeft(float fDT);
		void moveRight(float fDT);
		void moveNone(float fDT);
		void jump();

		//void localX(float p_value);
		//void localY(float p_value);

		float speed();

		virtual void update(float p_delta);
		virtual void render(sf::RenderWindow* p_window);
};

#endif