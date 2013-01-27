#ifndef WORLD_HPP
#define WORLD_HPP

#pragma once

#include <vector>
#include "parallax.hpp"
#include "world_entity.hpp"
#include "player.hpp"

class World
{
	private:
		
		Parallax m_background;
		Parallax m_foreground;
		std::vector<WorldEntity*> m_entities;
		Player* m_pPlayer;

		std::string buildParallaxPath(std::string p_name, int p_upgrade);
		void handle_event(const sf::Event &p_event);
		void updateEntities(float p_delta);
		void renderEntities(sf::RenderWindow* p_window);

	public:

		World();
		virtual ~World();

		void initialize();
		void Destroy();

		Player& GetPrimaryPlayer();

		void update(float p_deltaTime);
		void render(sf::RenderWindow* p_window);

		void addEntity(WorldEntity* p_entity);
		void removeEntity(WorldEntity* _pEntity );

		void handleKeypress();
};

#endif