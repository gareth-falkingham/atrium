#ifndef WORLD_ENTITY_HPP
#define WORLD_ENTITY_HPP

#pragma once

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

class WorldEntity
{
	protected:

		sf::Vector2f m_position;
		sf::Sprite m_sprite;
		sf::Texture m_texture;

	public:

		WorldEntity();
		virtual ~WorldEntity();

		void position(sf::Vector2f p_value);
		sf::Vector2f position();

		void sprite(sf::Sprite p_value);
		sf::Sprite sprite();
};

#endif