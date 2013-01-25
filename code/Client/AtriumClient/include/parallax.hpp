#ifndef PARALLAX_HPP
#define PARALLAX_HPP
#pragma once

#include <vector>
#include "parallax_layer.hpp"

class Parallax
{
	private:

		std::vector<ParallaxLayer> m_layers;

	public:

		void addLayer(const ParallaxLayer &p_layer);
		void update(float p_delta, float p_speed);
		void render(const sf::Window &p_window);
};

#endif