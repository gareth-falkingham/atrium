#include "parallax.hpp"

Parallax::Parallax(){}
Parallax::~Parallax(){}

void Parallax::addLayer(const ParallaxLayer &p_layer)
{
	m_layers.push_back(p_layer);
}

void Parallax::update(float p_deltaTime, float p_speed)
{
	ParallaxLayer currLayer;
	for (size_t i = 0; i < m_layers.size(); i++)
	{
		//currLayer = m_layers[i];
		//currLayer.scrollX(p_speed * currLayer.parallaxDepth() * (p_deltaTime * 20))
	}
}