#ifndef WORLD_HPP
#define WORLD_HPP

#pragma once

#include <vector>
#include "parallax.hpp"
#include "world_entity.hpp"

class World
{
	private:
		
		Parallax m_background;
		std::vector<WorldEntity*> m_entities;

		void updateEntities(float p_delta);
		void renderEntities(sf::RenderWindow* p_window);

	public:

		World();
		virtual ~World();

		void initialize();

		void update(float p_deltaTime);
		void render(sf::RenderWindow* p_window);

		void addEntity(WorldEntity* p_entity);

		void handleKeypress();
};

#endif