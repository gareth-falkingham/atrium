#ifndef PLAYER_HPP
#define PLAYER_HPP

#pragma once

#include <string>
#include <sstream>
#include <ostream>
#include <iomanip>

#include "const.hpp"
#include "assets.hpp"
#include "world_entity.hpp"

class Player : public WorldEntity
{
	private:

		std::string buildAssetPath(std::string type, int p_ext);
		void initializeSprite(int p_body, int p_head, int p_hair);

	public:
	
		Player();
		Player(int p_head, int p_hair, int p_body);
		virtual ~Player();

		virtual void update(float p_delta);
		virtual void render(sf::RenderWindow* p_window);
};

#endif