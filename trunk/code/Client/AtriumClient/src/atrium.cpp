#include "atrium.hpp"
#include "therakman.h"

// ----------------------------------------------------------------------
// Constants
// ----------------------------------------------------------------------

const sf::Color Atrium::CLEAR_COLOR = sf::Color(127, 127, 127);

// ----------------------------------------------------------------------
// Constructor
// ----------------------------------------------------------------------

Atrium::Atrium(){}

// ----------------------------------------------------------------------
// Deconstructor
// ----------------------------------------------------------------------

Atrium::~Atrium()
{
	delete m_world;
	delete m_player;
}

// ----------------------------------------------------------------------
// Initialize Window
// ----------------------------------------------------------------------

void Atrium::initializeWindow()
{
	Debug::log(LogLevel::INFO, "Atrium.initializeWindow", "Initializing Window");

	// setup the context settings
	m_glContext.antialiasingLevel = 4;
	m_glContext.depthBits = 32;
	m_glContext.majorVersion = 3;
	m_glContext.minorVersion = 0;
	m_glContext.stencilBits = 8;

	// create the window and set some limits
	m_window.create(sf::VideoMode(800, 480, 32), "Atrium v1.0", sf::Style::Titlebar | sf::Style::Close, m_glContext);
	m_window.setFramerateLimit(60);
	m_window.setVerticalSyncEnabled(true);
}

// ----------------------------------------------------------------------
// Initialize World
// ----------------------------------------------------------------------

void Atrium::initializeWorld()
{
	srand((unsigned)time(0)); 

	// create the world object
	m_world = new World();
	m_world->initialize();
}

// ----------------------------------------------------------------------
// Initialize World Entities
// ----------------------------------------------------------------------

void Atrium::initializeWorldEntities()
{
	// create the local player and populate network entities
	m_player = new Player(
		(rand() % Const::MAX_BODY_PIECES) + 1, 
		(rand() % Const::MAX_HEAD_PIECES) + 1, 
		(rand() % Const::MAX_HAIR_PIECES) + 1 
	);
	m_player->position(sf::Vector2f(Const::PLAYER_START_X, Const::PLAYER_START_Y));
	m_world->addEntity(m_player);
}

// ----------------------------------------------------------------------
// Run the Application
// ----------------------------------------------------------------------

void Atrium::run()
{
	// initialize the world
	initializeWorld();

	// initialize world Entities
	initializeWorldEntities();

	// initialize the window
	initializeWindow();

	// keep track of delta time
	sf::Time clockTime;

	//Start the Rak Man
	TheRakMan::Get();

	// main loop - continue until window is closed
	Debug::log(LogLevel::INFO, "Atrium.run", "Entering main loop");
	while(m_window.isOpen())
	{
		clockTime = m_clock.restart();
				
		// poll the events
		sf::Event event;
		while(m_window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed){ shutdown(); }
			else { handle_event(event); }
		}
	
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){ m_player->moveLeft(); }
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){ m_player->moveRight(); }
		else { m_player->moveNone(); } 

		// update/render
		update(clockTime.asSeconds());
		render();
	}

	//KILL the Rak Man.
	TheRakMan::Destroy();
}

// ----------------------------------------------------------------------
// Handle Events
// ----------------------------------------------------------------------

void Atrium::handle_event(const sf::Event &p_event)
{
	if (p_event.type == sf::Event::KeyPressed)
	{
		switch(p_event.key.code)
		{
			case sf::Keyboard::F1:
			{
				Debug::log(LogLevel::INFO, "Atrium.handle_event", "Screenshot Taken");
				m_window.capture().saveToFile("screen.png");
				break;
			}
		}
	}
}

// ----------------------------------------------------------------------
// Update the Application
// ----------------------------------------------------------------------

void Atrium::update(float p_delta)
{
	m_world->update(p_delta);
	TheRakMan::Get().Update( p_delta );
}

// ----------------------------------------------------------------------
// Render the Application
// ----------------------------------------------------------------------

void Atrium::render()
{
	m_window.clear(CLEAR_COLOR);
	m_world->render(&m_window);
	m_window.display();
}

// ----------------------------------------------------------------------
// Shutdown the Application
// ----------------------------------------------------------------------

void Atrium::shutdown()
{
	m_window.close();
}