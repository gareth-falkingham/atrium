#ifndef PARALLAX_HPP
#define PARALLAX_HPP
#pragma once

#include <vector>
#include "parallax_layer.hpp"
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

class Parallax
{
	private:

		std::vector<ParallaxLayer> m_layers;

	public:
		
		Parallax();
		~Parallax();

		void addLayer(ParallaxLayer p_layer);
		void update(float p_delta, float p_speed);
		void render(sf::RenderWindow* p_window);
};

#endif