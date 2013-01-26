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

		static const float SCROLL_SPEED;

		std::vector<ParallaxLayer> m_layers;

	public:
		
		Parallax();
		~Parallax();

		void addLayer(std::string p_filename, float p_depth, float p_xOffset = 0.0f, float p_yOffset = 0.0f);
		void update(float p_delta);
		void render(sf::RenderWindow* p_window);
};

#endif