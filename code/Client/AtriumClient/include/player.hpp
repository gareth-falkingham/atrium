#ifndef PLAYER_HPP
#define PLAYER_HPP

#pragma once

#include <string>
#include <sstream>
#include <ostream>
#include <iomanip>

#include "world_entity.hpp"
#include "assets.hpp"

class Player : WorldEntity
{
	private:

		static const int FRAMES = 4;
		static const int FRAME_WIDTH = 32;
		static const int FRAME_HEIGHT = 32;

		std::string buildAssetPath(std::string type, int p_ext);
		void initializeSprite(int p_body, int p_head, int p_hair);

	public:
	
		Player();
		Player(int p_head, int p_hair, int p_body);
		virtual ~Player();
};

#endif