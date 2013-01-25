#include "world_entity.hpp"

// ----------------------------------------------------------------------
// Constructor
// ----------------------------------------------------------------------

WorldEntity::WorldEntity(){}

// ----------------------------------------------------------------------
// Deconstructor
// ----------------------------------------------------------------------

WorldEntity::~WorldEntity(){}

// ----------------------------------------------------------------------
// Accessor for the Entities Position
// ----------------------------------------------------------------------

void WorldEntity::position(sf::Vector2f p_value){ m_position = p_value; }
sf::Vector2f WorldEntity::position(){ return m_position; }

// ----------------------------------------------------------------------
// Accessor for the Entities Sprite
// ----------------------------------------------------------------------

void WorldEntity::sprite(sf::Sprite p_value){ m_sprite = p_value; }
sf::Sprite WorldEntity::sprite(){ return m_sprite; }