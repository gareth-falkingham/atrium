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

void Parallax::addLayer(ParallaxLayer p_layer)
{
	m_layers.push_back(p_layer);
}

// ----------------------------------------------------------------------
// Update 
// ----------------------------------------------------------------------

void Parallax::update(float p_deltaTime, float p_speed)
{
	ParallaxLayer currLayer;
	for (size_t i = 0; i < m_layers.size(); i++)
	{
		//currLayer = m_layers[i];
		//currLayer.scrollX(p_speed * currLayer.parallaxDepth() * (p_deltaTime * 20))
	}
}

// ----------------------------------------------------------------------
// Render
// ----------------------------------------------------------------------

void Parallax::render(sf::RenderWindow* p_window)
{
	//ParallaxLayer p("assets/images/parallax_01.png", 0.0f);
	//p_window->draw(p.sprite());

	// iterate through the layers and render them to the window
	ParallaxLayer currLayer;
	for (size_t i = 0; i < m_layers.size(); i++)
	{
		currLayer = m_layers[i];
		p_window->draw(currLayer.sprite());
	}
}