#ifndef PARALLAX_LAYER_HPP
#define PARALLAX_LAYER_HPP

#pragma once

#include <SFML/Graphics.hpp>
#include "assets.hpp"

class ParallaxLayer
{
	private:

		float m_depth;
		sf::Texture m_texture;

	public:

		ParallaxLayer();
		~ParallaxLayer();

		void parallaxDepth(float p_number);
		float parallaxDepth();

		void initialize(std::string p_filename);
};

#endif