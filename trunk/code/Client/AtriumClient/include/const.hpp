#ifndef CONST_HPP
#define CONST_HPP

#pragma once

namespace Const
{
	static const int PLAYER_FRAME_COUNT = 4;
	static const int PLAYER_FRAME_WIDTH = 32;
	static const int PLAYER_FRAME_HEIGHT = 32;

	static const float PLAYER_START_X = 416;
	static const float PLAYER_START_Y = 224;
	
	static const float SCROLL_SPEED = 0.0f;

	static const float WORLD_GRAVITY = 9.8f;

	static const float GROUND_Y = 420.0f;

	static const unsigned int MAX_BODY_PIECES = 2;
	static const unsigned int MAX_HEAD_PIECES = 3;
	static const unsigned int MAX_HAIR_PIECES = 3;
}

#endif