#include "world.hpp"

World::World(){}
World::~World(){}

void World::initialize()
{
	m_background.addLayer(ParallaxLayer("parallax_01.png", 0.3));
	m_background.addLayer(ParallaxLayer("parallax_02.png", 0.4));
	m_background.addLayer(ParallaxLayer("parallax_03.png", 0.5));
	m_background.addLayer(ParallaxLayer("parallax_04.png", 0.6));
	m_background.addLayer(ParallaxLayer("parallax_05.png", 0.7));
	m_background.addLayer(ParallaxLayer("parallax_06.png", 0.8));
}

void World::update(float p_delta)
{
}

void World::render(const sf::Window &m_window)
{
	m_background.render(m_window);
}

void World::addEntity(WorldEntity p_entity)
{
	m_entities.push_back(p_entity);
}