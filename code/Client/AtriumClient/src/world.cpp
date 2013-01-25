#include "world.hpp"

World::World(){}
World::~World(){}

void World::addEntity(WorldEntity p_entity)
{
	m_entities.push_back(p_entity);
}