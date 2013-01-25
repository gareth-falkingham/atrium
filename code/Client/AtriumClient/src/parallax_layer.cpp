#include "parallax_layer.hpp"

ParallaxLayer::ParallaxLayer()
{
}

ParallaxLayer::~ParallaxLayer()
{
}

void ParallaxLayer::parallaxDepth(float p_value){ m_depth = p_value; }
float ParallaxLayer::parallaxDepth(){ return m_depth; }

void ParallaxLayer::initialize(std::string p_filename)
{
	m_left.setTexture(*Assets::getTexture(p_filename));
	m_rightt.setTexture(*Assets::getTexture(p_filename));
}
