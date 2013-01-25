#include "parallax_layer.hpp"

// ----------------------------------------------------------------------
// Constructor
// ----------------------------------------------------------------------

ParallaxLayer::ParallaxLayer()
{
	m_depth = 0.0f;
}

// ----------------------------------------------------------------------
// Overloaded Constructor
// ----------------------------------------------------------------------

ParallaxLayer::ParallaxLayer(std::string p_filename, float p_depth)
{
	m_depth = p_depth;
	initialize(p_filename);
}

// ----------------------------------------------------------------------
// Deconstructor
// ----------------------------------------------------------------------

ParallaxLayer::~ParallaxLayer(){}

// ----------------------------------------------------------------------
// Accessor for the Parallax Depth
// ----------------------------------------------------------------------

void ParallaxLayer::parallaxDepth(float p_value){ m_depth = p_value; }
float ParallaxLayer::parallaxDepth(){ return m_depth; }

// ----------------------------------------------------------------------
// Getter for the Parallax Sprite
// ----------------------------------------------------------------------

sf::Sprite ParallaxLayer::sprite() { return m_sprite; }

// ----------------------------------------------------------------------
// Initialize the Parallax Layer
// ----------------------------------------------------------------------

void ParallaxLayer::initialize(std::string p_filename)
{
	m_texture = Assets::getInstance()->getTexture(p_filename);
	m_sprite.setTexture(m_texture, false);
}
