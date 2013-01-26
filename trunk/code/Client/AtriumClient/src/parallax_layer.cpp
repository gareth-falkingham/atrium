#include "parallax_layer.hpp"

// ----------------------------------------------------------------------
// Constructor
// ----------------------------------------------------------------------

ParallaxLayer::ParallaxLayer()
{
	m_depth = 0.0f;
	m_xOffset = 0.0f;
	m_yOffset = 0.0f;
	m_xScroll = 0.0f;
	m_yScroll = 0.0f;
}

// ----------------------------------------------------------------------
// Overloaded Constructor
// ----------------------------------------------------------------------

ParallaxLayer::ParallaxLayer(std::string p_filename, float p_depth, float p_xOffset, float p_yOffset, bool p_repeat)
{
	m_depth = p_depth;
	m_xOffset = p_xOffset;
	m_yOffset = p_yOffset;
	m_xScroll = 0.0f;
	m_yScroll = 0.0f;
	initialize(p_filename, p_repeat);

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
// Accessor for the Sprite offset X
// ----------------------------------------------------------------------

void ParallaxLayer::xOffset(float p_value)
{ 
	m_xOffset = p_value; 
	m_sprite.setPosition(m_xOffset, m_xOffset);
}
float ParallaxLayer::xOffset(){ return m_xOffset; }

// ----------------------------------------------------------------------
// Accessor for the Sprite offset Y
// ----------------------------------------------------------------------

void ParallaxLayer::yOffset(float p_value)
{ 
	m_yOffset = p_value; 
	m_sprite.setPosition(m_xOffset, m_yOffset);
}
float ParallaxLayer::yOffset(){ return m_yOffset; }

// ----------------------------------------------------------------------
// Getter for the Parallax Sprite
// ----------------------------------------------------------------------

sf::Sprite ParallaxLayer::sprite() { return m_sprite; }

// ----------------------------------------------------------------------
// Initialize the Parallax Layer
// ----------------------------------------------------------------------

void ParallaxLayer::initialize(std::string p_filename, bool p_repeat)
{
	m_texture = Assets::getInstance()->getTexture(p_filename);
	m_texture->setRepeated(p_repeat);
	m_sprite.setTexture((*m_texture), false);
	m_sprite.setPosition(m_xOffset, m_yOffset);
}

// ----------------------------------------------------------------------
// Scroll the layer on the x-axis
// ----------------------------------------------------------------------

void ParallaxLayer::scrollX(float p_amount)
{
	m_xScroll += p_amount;
	sf::IntRect texRect = m_sprite.getTextureRect();
	sf::IntRect rect(texRect.left, texRect.top, texRect.width, texRect.height);
	rect.left = (int)m_xScroll;
	m_sprite.setTextureRect(rect);
}