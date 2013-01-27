#include "world.hpp"
#include "therakman.h"
#include "aiplayer.h"

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
	//m_background.addLayer(buildParallaxPath("parallax_01", 1), Const::PARALLAX_LAYER_1_DEPTH);
	if (Const::COMPLETE_HEARTS >= Const::PARALLAX_LAYER_1_UPGRADE){ m_background.addLayer(buildParallaxPath("parallax_01", 2), 0.0f); }
	//m_background.addLayer(buildParallaxPath("parallax_02", 1), Const::PARALLAX_LAYER_2_DEPTH);
	if (Const::COMPLETE_HEARTS >= Const::PARALLAX_LAYER_2_UPGRADE){ m_background.addLayer(buildParallaxPath("parallax_02", 2), Const::PARALLAX_LAYER_2_DEPTH); }
	//m_background.addLayer(buildParallaxPath("parallax_03", 1), Const::PARALLAX_LAYER_3_DEPTH);
	if (Const::COMPLETE_HEARTS >= Const::PARALLAX_LAYER_3_UPGRADE){ m_background.addLayer(buildParallaxPath("parallax_03", 2), Const::PARALLAX_LAYER_3_DEPTH); }
	//m_background.addLayer(buildParallaxPath("parallax_04", 1), Const::PARALLAX_LAYER_4_DEPTH);
	if (Const::COMPLETE_HEARTS >= Const::PARALLAX_LAYER_4_UPGRADE){ m_background.addLayer(buildParallaxPath("parallax_04", 2), Const::PARALLAX_LAYER_4_DEPTH); }
	//m_background.addLayer(buildParallaxPath("parallax_05", 1), Const::PARALLAX_LAYER_5_DEPTH);
	if (Const::COMPLETE_HEARTS >= Const::PARALLAX_LAYER_5_UPGRADE){ m_background.addLayer(buildParallaxPath("parallax_05", 2), Const::PARALLAX_LAYER_5_DEPTH); }
	//m_background.addLayer(buildParallaxPath("parallax_06", 1), Const::PARALLAX_LAYER_6_DEPTH);
	if (Const::COMPLETE_HEARTS >= Const::PARALLAX_LAYER_6_UPGRADE){ m_background.addLayer(buildParallaxPath("parallax_06", 2), Const::PARALLAX_LAYER_6_DEPTH, 0.0f, -60.0f); }

	// ground
	m_background.addLayer("assets/images/parallax_07.png", 0.0f, 0.0f, 420.0f);

	// Atrium backgorund
	m_background.addLayer("assets/images/atrium.png", 1.0f, 0.0f, 0.0f, false);

	// initialize the atrium building
	m_foreground.addLayer("assets/images/atrium_front.png", 1.0f, 0.0f, 0.0f, false);

	m_pPlayer = new Player();
	m_pPlayer->randomiseBody();
	m_pPlayer->GetPlayerData().x = 0.0f; // worldX starts at 0
	m_pPlayer->GetPlayerData().y = Const::PLAYER_START_Y; // worldY starts at normal start y

	//m_pPlayer->generateHeart();

	m_pPlayer->GetPlayerData().x = (Const::PLAYER_START_X);
	m_pPlayer->GetPlayerData().y = (Const::PLAYER_START_Y);

	addEntity( m_pPlayer );

	//Start the Rak Man
	TheRakMan::Get().m_pPrimaryPlayer = m_pPlayer;
	TheRakMan::Get().m_pWorld = this;

	AIPlayer* npc;
	int i = 0;
	while (i < 10)
	{
		npc = new AIPlayer();
		npc->randomiseBody();
		npc->GetPlayerData().x = static_cast<float>(rand() % 800);

		npc->GetPlayerData().y = (Const::PLAYER_START_Y);
		addEntity(npc);

		i++;
	}
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
	float scrollValue = (0.1f*(m_pPlayer->GetPlayerData().x-400.0f));

	m_background.scrollX(scrollValue);
	m_background.update(p_delta);

	// update the player entities
	for (size_t i = 0; i < m_entities.size(); i++){ m_entities[i]->update(p_delta); }

	// scroll the foreground based on player speed
	m_foreground.scrollX(scrollValue);
	m_foreground.update(p_delta);

	updateInteraction( p_delta );
}

void World::updateInteraction( float p_deltaTime )
{
	if( m_pPlayer->GetInteractionTime() > Const::PLAYER_MIN_INTERACTION_TIME )
	{
		for( unsigned int i = 0 ; i < m_entities.size() ; ++i)
		{
			if( m_entities[i] != m_pPlayer )
			{
				if( m_entities[i]->GetInteractionTime() > Const::PLAYER_MIN_INTERACTION_TIME &&
					abs( m_entities[i]->GetXPosition() - m_pPlayer->GetXPosition() ) < Const::PLAYER_MIN_INTERACTION_DISTANCE )
				{
					if( Heart::IsHeartMatch( m_pPlayer->GetHeartID(), m_entities[i]->GetHeartID() ) )
					{
						//YOU HAVE INTERACTED. CONGRATULATION, YOU WIN THE GAME.
						Debug::log(INFO,"updateInteraction", "YOU WON THE FREAKIN GAME" );
					}
					else
					{
						Debug::log(INFO,"updateInteraction", "Interaction was successful but hearts do not match." );
					}
				}
			}
		}
	}
}

// ----------------------------------------------------------------------
// Build an asset path given a type (parallax_01) and integer
// ----------------------------------------------------------------------

std::string World::buildParallaxPath(std::string p_type, int p_ext)
{
	std::ostringstream ss;
	ss << "assets/images/";
	ss << p_type << "_";
	ss << std::setw(2) << std::setfill('0') << p_ext;
	ss << ".png";
	return ss.str();
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