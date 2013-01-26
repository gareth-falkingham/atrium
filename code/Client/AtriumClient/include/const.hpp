#ifndef CONST_HPP
#define CONST_HPP

#pragma once

namespace Const
{
	static const int PLAYER_FRAME_COUNT = 4;
	static const int PLAYER_FRAME_WIDTH = 32;
	static const int PLAYER_FRAME_HEIGHT = 32;

	static const float PLAYER_START_X = 400;
	static const float PLAYER_START_Y = 224;
	
	static const float PLAYER_ACCELERATION = 0.25f;
	static const float PLAYER_DECELERATION = 0.25f;
	static const float PLAYER_MAX_SPEED = 6.0f;

	static const int PLAYER_LEFT_BOUND = 200;
	static const int PLAYER_RIGHT_BOUND = 600;

	static const float WORLD_GRAVITY = 9.8f;

	static const float GROUND_Y = 435.0f;

	static const float ATRIUM_OFFSET_X = 273;
	static const float ATRIUM_OFFSET_Y = 105;

	static const unsigned int MAX_BODY_PIECES = 6;
	static const unsigned int MAX_HEAD_PIECES = 4;
	static const unsigned int MAX_HAIR_PIECES = 6;
}

#endif