#include "parallax.hpp"

// ----------------------------------------------------------------------
// Constructor
// ----------------------------------------------------------------------

Parallax::Parallax(){}

// ----------------------------------------------------------------------
// Deconstructor
// ----------------------------------------------------------------------

Parallax::~Parallax(){}

// ----------------------------------------------------------------------
// Add a new Parallax Layer
// ----------------------------------------------------------------------

void Parallax::addLayer(std::string p_filename, float p_depth)
{
	ParallaxLayer p(p_filename, p_depth);
	m_layers.push_back(p);
}

// ----------------------------------------------------------------------
// Update 
// ----------------------------------------------------------------------

void Parallax::update(float p_deltaTime, float p_speed)
{
	ParallaxLayer currLayer;
	for (size_t i = 0; i < m_layers.size(); i++)
	{
		//m_layers[i].scrollX(p_speed * currLayer.parallaxDepth() * (p_deltaTime * 20))
	}
}

// ----------------------------------------------------------------------
// Render
// ----------------------------------------------------------------------

void Parallax::render(sf::RenderWindow* p_window)
{
	// iterate through the layers and render them to the window
	ParallaxLayer currLayer;
	for (size_t i = 0; i < m_layers.size(); i++)
	{
		p_window->draw(m_layers[i].sprite());
	}
}