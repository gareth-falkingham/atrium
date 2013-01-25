#ifndef ASSETS_HPP
#define ASSETS_HPP

#pragma once

#include <map>
#include <string>

#include <SFML/Graphics.hpp>
#include "debug.hpp"

class Assets
{
	private:
		static std::map<std::string, sf::Image> m_images;
		static std::map<std::string, sf::Texture> m_textures;

	public:
		Assets();
		~Assets();
		static sf::Image* getImage(std::string p_file);
		static sf::Texture* getTexture(std::string p_file);
};

#endif