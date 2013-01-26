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
		std::map<std::string, sf::Image> m_images;
		std::map<std::string, sf::Texture> m_textures;
		static Assets* m_instance;
		Assets();
		~Assets();

	public:
		static Assets* getInstance(); 
		sf::Image getImage(std::string p_file);
		sf::Texture getTexture(std::string p_file);
};

#endif