#include "world.hpp"
#include "therakman.h"

// ----------------------------------------------------------------------
// Constructor
// ----------------------------------------------------------------------

World::World(): 
m_pPlayer(0)
{
}

// ----------------------------------------------------------------------
// Deconstructor
// ----------------------------------------------------------------------

World::~World()
{
	delete m_pPlayer;
	m_pPlayer = 0;
}

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
	m_background.addLayer("assets/images/parallax_07.png", 0.0f, 0.0f, 420.0f);
	m_background.addLayer("assets/images/atrium.png", 1.0f, 0.0f, 0.0f, false);

	// initialize the atrium building
	m_foreground.addLayer("assets/images/atrium_front.png", 1.0f, 0.0f, 0.0f, false);

	m_pPlayer = new Player(
		(rand() % Const::MAX_BODY_PIECES) + 1, 
		(rand() % Const::MAX_HEAD_PIECES) + 1, 
		(rand() % Const::MAX_HAIR_PIECES) + 1 
	);
	m_pPlayer->GetPlayerData().x = Const::PLAYER_START_X;
	m_pPlayer->GetPlayerData().y = Const::PLAYER_START_Y;

	addEntity( m_pPlayer );

	//Start the Rak Man
	TheRakMan::Get().m_pPrimaryPlayer = m_pPlayer;
	TheRakMan::Get().m_pWorld = this;
}

void World::Destroy()
{
	m_pPlayer->SendDisconnectPacket();
}

// ----------------------------------------------------------------------
// Update the World
// ----------------------------------------------------------------------

void World::update(float p_delta)
{
	// scroll the background based on player speed
	m_background.scrollX(m_pPlayer->speed());
	m_background.update(p_delta);

	// update the player entities
	for (size_t i = 0; i < m_entities.size(); i++){ m_entities[i]->update(p_delta); }

	// scroll the foreground based on player speed
	m_foreground.scrollX(m_pPlayer->speed());
	m_foreground.update(p_delta);

}

// ----------------------------------------------------------------------
// Handle Events
// ----------------------------------------------------------------------

void World::handle_event(const sf::Event &p_event)
{
	/*if (p_event.type == sf::Event::KeyPressed)
	{
		switch(p_event.key.code)
		{
		default:
			{
				break;
			}
		}
	}*/
}

// ----------------------------------------------------------------------
// Render the World
// ----------------------------------------------------------------------

void World::render(sf::RenderWindow* m_window)
{
	m_background.render(m_window);
	for (size_t i = 0; i < m_entities.size(); i++)
	{
		m_entities[i]->render(m_window);
	}
	m_foreground.render(m_window);
}

// ----------------------------------------------------------------------
// Add a World Entity
// ----------------------------------------------------------------------

void World::addEntity(WorldEntity* p_entity)
{
	m_entities.push_back((p_entity));
}

void World::removeEntity(WorldEntity* _pEntity )
{
	if( m_entities.size() > 0 )
	{
		std::vector<WorldEntity*>::iterator iter;
		for( iter = m_entities.begin() ; iter != m_entities.end() ; ++iter )
		{
			if( *iter == _pEntity )
			{
				m_entities.erase(iter);
				break;
			}
		}
	}
}

Player& World::GetPrimaryPlayer()
{
	return *m_pPlayer;
}