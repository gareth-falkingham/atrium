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
		sf::Texture* m_loadingTexture;
		sf::Texture* m_continueTexture;
		sf::Sprite* m_bgSprite;
		sf::Sprite* m_infoSprite;
		Atrium* m_atrium;

	public:
		
		Preloader(Atrium* p_atrium);
		virtual ~Preloader();

		void dispose();

		void show(sf::RenderWindow* p_window);
		void showContinue(sf::RenderWindow* p_window);
};

#endif