#ifndef ATRIUM_HPP
#define ATRIUM_HPP

#pragma once

#include <ctime>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include "debug.hpp"
#include "world.hpp"
#include "player.hpp"
#include "assets.hpp"
#include "preloader.hpp"

typedef void (Atrium::*CB_StartGame)(void);

class Atrium
{
	private:

		// window variables
		sf::RenderWindow* m_window;
		sf::ContextSettings* m_glContext;

		// timing stuff
		sf::Clock m_clock;

		// world stuff
		World* m_world;

		// initialization functions
		Preloader* m_preloader;

		void initializeWindow();
		void initializeWorld();

		void handle_event(const sf::Event &p_event);
		void handle_input();
		void update(float p_delta);
		void render();
		void shutdown();

	public:
		
		// con - decon
		Atrium();
		~Atrium();

		// main entry point
		void run(); // display preloader and initialize
		void startGame(); // once preloader fires exit start game
};

#endif