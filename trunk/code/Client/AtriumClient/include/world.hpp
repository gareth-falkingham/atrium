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
		std::vector<WorldEntity> m_entities;

	public:

		World();
		virtual ~World();

		void initialize();

		void update(float p_deltaTime);
		void render(const sf::Window &p_window);

		void addEntity(WorldEntity p_entity);
		void updateEntities();
		void renderEntities();
};

#endif