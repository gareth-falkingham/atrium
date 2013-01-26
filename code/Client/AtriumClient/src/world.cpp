#include "world.hpp"

// ----------------------------------------------------------------------
// Constructor
// ----------------------------------------------------------------------

World::World(){}

// ----------------------------------------------------------------------
// Deconstructor
// ----------------------------------------------------------------------

World::~World(){}

// ----------------------------------------------------------------------
// Initialize the World
// ----------------------------------------------------------------------

void World::initialize()
{
	// initialize the parallax layers
	m_background.addLayer("assets/images/parallax_01.png", 0.3f);
	m_background.addLayer("assets/images/parallax_02.png", 0.4f);
	m_background.addLayer("assets/images/parallax_03.png", 0.5f);
	m_background.addLayer("assets/images/parallax_04.png", 0.6f);
	m_background.addLayer("assets/images/parallax_05.png", 0.7f);
	m_background.addLayer("assets/images/parallax_06.png", 0.8f);
}

// ----------------------------------------------------------------------
// Update the World
// ----------------------------------------------------------------------

void World::update(float p_delta)
{
	updateEntities(p_delta);
}

// ----------------------------------------------------------------------
// Render the World
// ----------------------------------------------------------------------

void World::render(sf::RenderWindow* m_window)
{
	m_background.render(m_window);
}

// ----------------------------------------------------------------------
// Add a World Entity
// ----------------------------------------------------------------------

void World::addEntity(WorldEntity p_entity)
{
	m_entities.push_back(p_entity);
}

// ----------------------------------------------------------------------
// Update the Entity list
// ----------------------------------------------------------------------

void World::updateEntities(float p_delta)
{
	// move all the peoples
}

// ----------------------------------------------------------------------
// Render the Entity list
// ----------------------------------------------------------------------

void World::renderEntities(sf::RenderWindow* p_window)
{
	// render all the peoples
}