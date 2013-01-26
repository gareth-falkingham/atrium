#ifndef PARALLAX_HPP
#define PARALLAX_HPP
#pragma once

#include <vector>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "const.hpp"
#include "parallax_layer.hpp"

class Parallax
{
	private:

		std::vector<ParallaxLayer> m_layers;
		float m_scrollX;

	public:
		
		Parallax();
		~Parallax();

		void addLayer(std::string p_filename, float p_depth, float p_xOffset = 0.0f, float p_yOffset = 0.0f, bool p_repeat = true);
		void update(float p_delta);
		void render(sf::RenderWindow* p_window);

		void scrollX(float p_value);
};

#endif