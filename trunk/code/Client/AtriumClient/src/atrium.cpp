#include "atrium.hpp"
#include "therakman.h"

// ----------------------------------------------------------------------
// Constructor
// ----------------------------------------------------------------------

Atrium::Atrium()
{
}

// ----------------------------------------------------------------------
// Deconstructor
// ----------------------------------------------------------------------

Atrium::~Atrium()
{
	delete m_world;
	m_world = 0;
	delete m_window;
	m_window = 0;
	delete m_glContext;
	m_glContext = 0;
}

// ----------------------------------------------------------------------
// Initialize Window
// ----------------------------------------------------------------------

void Atrium::initializeWindow()
{
	Debug::log(LogLevel::INFO, "Atrium.initializeWindow", "Initializing Window");

	// setup the context settings
	m_glContext = new sf::ContextSettings();
	m_glContext->antialiasingLevel = 4;
	m_glContext->depthBits = 32;
	m_glContext->majorVersion = 3;
	m_glContext->minorVersion = 0;
	m_glContext->stencilBits = 8;

	// create the window and set some limits
	m_window = new sf::RenderWindow();
	m_window->create(sf::VideoMode(800, 480, 32), "Atrium v1.0", sf::Style::Titlebar | sf::Style::Close, (*m_glContext));
	m_window->setFramerateLimit(60);
	m_window->setVerticalSyncEnabled(true);
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
// Run the Application
// ----------------------------------------------------------------------

void Atrium::run()
{
	// initialize the window
	initializeWindow();

	// new up the preloader and display it
	m_preloader = new Preloader(this);
	m_preloader->show(m_window);

	// initialize the world
	initializeWorld();

	// loading finished show the continue button
	m_preloader->showContinue(m_window);
}

void Atrium::startGame()
{
	m_preloader->dispose();
	delete m_preloader;
	m_preloader = 0;

	// keep track of delta time
	sf::Time clockTime;

	// main loop - continue until window is closed
	Debug::log(LogLevel::INFO, "Atrium.run", "Entering main loop");
	while(m_window->isOpen())
	{
		clockTime = m_clock.restart();
				
		// poll the events
		sf::Event event;
		while(m_window->pollEvent(event))
		{
			handle_event(event);
			if (event.type == sf::Event::Closed){ shutdown(); }
		}

		// handle any non-event input
		float fDT = clockTime.asSeconds();

		handle_input(fDT);

		// update/render
		update(fDT);
		render();
	}

	m_world->Destroy();
	delete Heart::sm_pTexture;
	Heart::sm_pTexture = 0;

	// KILL the Rak Man.
	TheRakMan::Destroy();
}

// ----------------------------------------------------------------------
// Handle the Events
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
				m_window->capture().saveToFile("screen.png");
				break;
			}
			case sf::Keyboard::F2:
			{
				if (Const::COMPLETE_HEARTS == 250){ break; }
				Debug::log(LogLevel::INFO, "Atrium.handle_event", "Incrementing Hearts Matched: %d", Const::COMPLETE_HEARTS++);
				m_world->incrementHeartsMatched();
				break;
			}
			case sf::Keyboard::F3:
			{
				if (Const::COMPLETE_HEARTS == 0){ break; }
				Debug::log(LogLevel::INFO, "Atrium.handle_event", "Decrementing Hearts Matched: %d", Const::COMPLETE_HEARTS--);
				m_world->decrementHeartsMatched();
				break;
			}
			case sf::Keyboard::Space:
			{
				if( m_world->GetPrimaryPlayer().GetXPosition() > 330 && 
					m_world->GetPrimaryPlayer().GetXPosition() < 490 )
				{
					m_world->GetPrimaryPlayer().generateHeart();
				}
				break;
			}
		}
	}
}

// ----------------------------------------------------------------------
// Handle non-Event input
// ----------------------------------------------------------------------

void Atrium::handle_input(float fDT)
{
	// check for non-event input
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{ 
		m_world->GetPrimaryPlayer().moveLeft(fDT);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{ 
		m_world->GetPrimaryPlayer().moveRight(fDT);
	}
	else 
	{ 
		m_world->GetPrimaryPlayer().moveNone(fDT);
	} 

	if( sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
 		if( m_world->GetPrimaryPlayer().GetXPosition() <= 330 || 
			m_world->GetPrimaryPlayer().GetXPosition() >= 490 )
		{
			m_world->GetPrimaryPlayer().GetPlayerData().isInteracting = true;
		}
	}
	else
	{
		m_world->GetPrimaryPlayer().GetPlayerData().isInteracting = false;
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
	m_window->clear(Const::CLEAR_COLOR);
	m_world->render(m_window);
	m_window->display();
}

// ----------------------------------------------------------------------
// Shutdown the Application
// ----------------------------------------------------------------------

void Atrium::shutdown()
{
	m_window->close();
}