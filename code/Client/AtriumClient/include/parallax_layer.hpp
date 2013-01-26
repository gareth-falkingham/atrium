#ifndef PARALLAX_LAYER_HPP
#define PARALLAX_LAYER_HPP

#pragma once

#include <SFML/Graphics.hpp>
#include "assets.hpp"

class ParallaxLayer
{
	private:

		float m_depth;
		sf::Texture* m_texture;
		sf::Sprite m_sprite;

	public:

		ParallaxLayer();
		ParallaxLayer(std::string p_filename, float p_depth);
		~ParallaxLayer();

		void parallaxDepth(float p_number);
		float parallaxDepth();

		sf::Sprite sprite();
		
		void initialize(std::string p_filename);
};

#endif