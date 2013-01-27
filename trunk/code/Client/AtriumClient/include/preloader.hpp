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

	public:
		
		Preloader(Atrium* p_atrium);
		virtual ~Preloader();

		void dispose();

		void show();

		void showContinue();
};

#endif