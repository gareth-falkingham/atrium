#ifndef CONST_HPP
#define CONST_HPP

#pragma once

#include <SFML/Graphics.hpp>

namespace Const
{
	static const int PLAYER_FRAME_COUNT = 4;
	static const int PLAYER_FRAME_WIDTH = 32;
	static const int PLAYER_FRAME_HEIGHT = 32;

	static const float PLAYER_START_X = 400;
	static const float PLAYER_START_Y = 224;
	
	static const float PLAYER_ACCELERATION = 100.0f;
	//static const float PLAYER_DECELERATION = 10.0f;
	static const float PLAYER_MAX_SPEED = 200.0f;

	static const float PARALLAX_LAYER_1_DEPTH = 0.3f;
	static const float PARALLAX_LAYER_2_DEPTH = 0.4f;
	static const float PARALLAX_LAYER_3_DEPTH = 0.5f;
	static const float PARALLAX_LAYER_4_DEPTH = 0.6f;
	static const float PARALLAX_LAYER_5_DEPTH = 0.7f;
	static const float PARALLAX_LAYER_6_DEPTH = 0.8f;

	static const unsigned int PARALLAX_LAYER_1_UPGRADE = 250;
	static const unsigned int PARALLAX_LAYER_2_UPGRADE = 100;
	static const unsigned int PARALLAX_LAYER_3_UPGRADE = 50;
	static const unsigned int PARALLAX_LAYER_4_UPGRADE = 25;
	static const unsigned int PARALLAX_LAYER_5_UPGRADE = 10;
	static const unsigned int PARALLAX_LAYER_6_UPGRADE = 1;

	static const int PLAYER_LEFT_BOUND = 200;
	static const int PLAYER_RIGHT_BOUND = 600;

	static const float WORLD_GRAVITY = 9.8f;

	static const float GROUND_Y = 435.0f;

	static const float ATRIUM_OFFSET_X = 273;
	static const float ATRIUM_OFFSET_Y = 105;

	static const unsigned int MAX_BODY_PIECES = 6;
	static const unsigned int MAX_HEAD_PIECES = 6;
	static const unsigned int MAX_HAIR_PIECES = 6;

	static const unsigned int COMPLETE_HEARTS = 250;

	static const sf::Color CLEAR_COLOR = sf::Color(127, 127, 127);
}

#endif