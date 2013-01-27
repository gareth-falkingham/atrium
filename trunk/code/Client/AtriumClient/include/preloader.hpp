#ifndef PRELOADER_HPP
#define PRELOADER_HPP
#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "assets.hpp"
#include "const.hpp"

class Atrium;

class Preloader
{
	private:

		sf::Texture* m_texture;
		sf::Sprite* m_sprite;
		Atrium* m_atrium;
		sf::Font* m_font;
		sf::Text* m_loadingText;
		sf::Text* m_continueText;

	public:
		
		Preloader(Atrium* p_atrium);
		virtual ~Preloader();

		void dispose();

		void show(sf::RenderWindow* p_window);
		void showContinue(sf::RenderWindow* p_window);
};

#endif