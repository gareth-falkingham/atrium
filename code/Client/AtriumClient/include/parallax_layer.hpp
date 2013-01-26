#ifndef PARALLAX_LAYER_HPP
#define PARALLAX_LAYER_HPP

#pragma once

#include <SFML/Graphics.hpp>
#include "assets.hpp"

class ParallaxLayer
{
	private:

		float m_depth;

		float m_xOffset;
		float m_yOffset;

		float m_xScroll;
		float m_yScroll;

		sf::Texture* m_texture;
		sf::Sprite m_sprite;

	public:

		ParallaxLayer();
		ParallaxLayer(std::string p_filename, float p_depth, float p_xOffset, float p_yOffset);
		~ParallaxLayer();

		void parallaxDepth(float p_number);
		float parallaxDepth();

		void xOffset(float p_value);
		float xOffset();

		void yOffset(float p_value);
		float yOffset();

		void scrollX(float p_amount);
		void scrollY(float p_amount);

		sf::Sprite sprite();
		
		void initialize(std::string p_filename);
};

#endif