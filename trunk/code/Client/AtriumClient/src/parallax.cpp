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

void Parallax::addLayer(std::string p_filename, float p_depth, float p_xOffset, float p_yOffset)
{
	ParallaxLayer p(p_filename, p_depth, p_xOffset, p_yOffset);
	m_layers.push_back(p);
}

// ----------------------------------------------------------------------
// Update 
// ----------------------------------------------------------------------

void Parallax::update(float p_deltaTime)
{
	for (size_t i = 0; i < m_layers.size(); i++)
	{
		ParallaxLayer& currLayer = m_layers[i];
		currLayer.scrollX(Const::SCROLL_SPEED * currLayer.parallaxDepth() * (p_deltaTime * 20));
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