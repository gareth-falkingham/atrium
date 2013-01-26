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

class Player : public WorldEntity, public NetworkPlayer{
	private:

		Direction m_facing;	
		float m_speed;
		AnimatedSprite* m_animatedSprite;
		std::string buildAssetPath(std::string type, int p_ext);
		void initializeSprite(int p_body, int p_head, int p_hair);

	public:
	
		Player();
		Player(int p_head, int p_hair, int p_body);
		virtual ~Player();

		void moveLeft();
		void moveRight();
		void moveNone();

		virtual void update(float p_delta);
		virtual void render(sf::RenderWindow* p_window);
};

#endif