#ifndef ATRIUM_HPP
#define ATRIUM_HPP

#pragma once

#include <ctime>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include "debug.hpp"
#include "world.hpp"
#include "player.hpp"

class Atrium
{
	private:

		// constants
		static const sf::Color CLEAR_COLOR;

		// window variables
		sf::RenderWindow m_window;
		sf::ContextSettings m_glContext;

		// timing stuff
		sf::Clock m_clock;

		// world stuff
		World* m_world;

		// player
		Player* m_player;

		// initialization functions
		void initializeWindow();
		void initializeWorld();
		void initializeWorldEntities();

		void handle_event(const sf::Event &p_event);
		void update(float p_delta);
		void render();
		void shutdown();

	public:
		
		// con - decon
		Atrium();
		~Atrium();

		// main entry point
		void run();
};

#endif