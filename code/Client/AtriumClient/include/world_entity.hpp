#ifndef WORLD_ENTITY_HPP
#define WORLD_ENTITY_HPP

#pragma once

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#include "debug.hpp"

class WorldEntity
{
	protected:

		sf::Texture* m_texture;
		sf::Sprite* m_sprite;
		//sf::Vector2f m_position;

	public:

		WorldEntity();
		virtual ~WorldEntity();

		//void position(sf::Vector2f p_value);
		//sf::Vector2f position();

		void sprite(sf::Sprite* p_value);
		sf::Sprite* sprite();

		virtual void update(float p_delta);
		virtual void render(sf::RenderWindow* p_window);
};

#endif