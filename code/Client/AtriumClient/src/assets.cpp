#include "assets.hpp"

// ----------------------------------------------------------------------
// Texture and Image maps
// ----------------------------------------------------------------------

Assets* Assets::m_instance = 0;

// ----------------------------------------------------------------------
// Constructor
// ----------------------------------------------------------------------

Assets::Assets(){}

// ----------------------------------------------------------------------
// Deconstructor
// ----------------------------------------------------------------------

Assets::~Assets(){}

Assets* Assets::getInstance()
{
	if (m_instance == NULL){ m_instance = new Assets(); }
	return m_instance;
}

// ----------------------------------------------------------------------
// Get Texture ( load a texture file and cache the results )
// ----------------------------------------------------------------------

sf::Texture* Assets::getTexture(std::string p_key)
{
	// attempt to find the resource key in the map
	std::map<std::string, sf::Texture>::iterator it = m_textures.find(p_key);

	// if it's found return it
	if (it != m_textures.end())
	{
		return &it->second;
	}
	else
	{
		Debug::log(LogLevel::EXCEPTION, "Assets::getTexture", "Loading '%s'", p_key.c_str());
		// load the texture from file and save it in the map
		sf::Texture tex;
		if (tex.loadFromFile(p_key))
		{
			Debug::log(LogLevel::EXCEPTION, "Assets::getTexture", "Loaded: Width: %d, Height:%d", tex.getSize().x, tex.getSize().y);
			m_textures[p_key] = tex;
			return getTexture(p_key); // do another search for it ?
		}
		else 
		{
			Debug::log(LogLevel::EXCEPTION, "Assets::getTexture", "'%s' -> failed to load file", p_key.c_str());
			return 0;
		}
	}
}

// ----------------------------------------------------------------------
// Get Image ( load an image file and cache the results )
// ----------------------------------------------------------------------

sf::Image* Assets::getImage(std::string p_key)
{
	// attempt to find the resource key in the map
	std::map<std::string, sf::Image>::iterator it = m_images.find(p_key);

	// if it's found return it
	if (it != m_images.end())
	{
		return &it->second;
	}
	else
	{
		// load the texture from file and save it in the map
		sf::Image img;
		if (img.loadFromFile(p_key))
		{
			m_images[p_key] = img;
			return getImage(p_key); // do another search for it ?
		}
		else 
		{
			Debug::log(LogLevel::EXCEPTION, "Assets::getImage", "'%s' -> failed to load file", p_key.c_str());
			return 0;
		}
	}
}