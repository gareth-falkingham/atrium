#include "parallax.hpp"

// ----------------------------------------------------------------------
// Constructor
// ----------------------------------------------------------------------

Parallax::Parallax()
{
	m_scrollX = 0.0f;
}

// ----------------------------------------------------------------------
// Deconstructor
// ----------------------------------------------------------------------

Parallax::~Parallax(){}

// ----------------------------------------------------------------------
// Add a new Parallax Layer
// ----------------------------------------------------------------------

void Parallax::addLayer(std::string p_filename, float p_depth, float p_xOffset, float p_yOffset, bool p_repeat)
{
	ParallaxLayer p(p_filename, p_depth, p_xOffset, p_yOffset, p_repeat);
	m_layers.push_back(p);
}

void Parallax::clearLayers()
{
	m_layers.clear();
}

// ----------------------------------------------------------------------
// Set the scrollX for the parallax
// ----------------------------------------------------------------------

void Parallax::scrollX(float p_value)
{
	m_scrollX = p_value;
}

// ----------------------------------------------------------------------
// Update 
// ----------------------------------------------------------------------

void Parallax::update(float p_deltaTime)
{
	for (size_t i = 0; i < m_layers.size(); i++)
	{
		ParallaxLayer& currLayer = m_layers[i];
		currLayer.scrollX(m_scrollX * currLayer.parallaxDepth());
	}
}

// ----------------------------------------------------------------------
// Render
// ----------------------------------------------------------------------

void Parallax::render(sf::RenderWindow* p_window)
{
	// iterate through the layers and render them to the window
	for (size_t i = 0; i < m_layers.size(); i++)
	{
		p_window->draw(m_layers[i].sprite());
	}
}