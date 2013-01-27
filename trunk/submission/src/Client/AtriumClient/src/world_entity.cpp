#include "world_entity.hpp"

// ----------------------------------------------------------------------
// Constructor
// ----------------------------------------------------------------------

WorldEntity::WorldEntity()
: m_fInteractionTime(0.0f)
{
	m_texture = 0;
	m_sprite = 0;
}

// ----------------------------------------------------------------------
// Deconstructor
// ----------------------------------------------------------------------

WorldEntity::~WorldEntity()
{
	delete m_texture;
	m_texture = 0;
	delete m_sprite;
	m_sprite = 0;
}

// ----------------------------------------------------------------------
// Accessor for the Entities Position
// ----------------------------------------------------------------------

//void WorldEntity::position(sf::Vector2f p_value){ m_position = p_value; }
//sf::Vector2f WorldEntity::position(){ return m_position; }

// ----------------------------------------------------------------------
// Accessor for the Entities Sprite
// ----------------------------------------------------------------------

void WorldEntity::sprite(sf::Sprite* p_value){ m_sprite = p_value; }
sf::Sprite* WorldEntity::sprite(){ return m_sprite; }

// ----------------------------------------------------------------------
// Update Entity
// ----------------------------------------------------------------------

void WorldEntity::update(float p_delta)
{
	// designed to be overloaded
}

// ----------------------------------------------------------------------
// Render Entity
// ----------------------------------------------------------------------

void WorldEntity::render(sf::RenderWindow* m_window)
{
	// designed to be overloaded
}