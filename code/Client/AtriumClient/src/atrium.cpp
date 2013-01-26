#include "atrium.hpp"

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

Atrium::~Atrium(){}

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
	m_world.initialize();
}

// ----------------------------------------------------------------------
// Run the Application
// ----------------------------------------------------------------------

void Atrium::run()
{
	// initialize the window
	initializeWindow();

	// initialize the world
	initializeWorld();

	// main loop - continue until window is closed
	Debug::log(LogLevel::INFO, "Atrium.run", "Entering main loop");
	while(m_window.isOpen())
	{
		// poll the events
		sf::Event event;
		while(m_window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed){ shutdown(); }
			else { handle_event(event); }
		}

		// update/render
		update(0.0f);
		render();
	}
}

// ----------------------------------------------------------------------
// Handle Events
// ----------------------------------------------------------------------

void Atrium::handle_event(const sf::Event &p_event)
{

}

// ----------------------------------------------------------------------
// Update the Application
// ----------------------------------------------------------------------

void Atrium::update(float p_delta)
{
	m_world.update(p_delta);
}

// ----------------------------------------------------------------------
// Render the Application
// ----------------------------------------------------------------------

void Atrium::render()
{
	m_window.clear(CLEAR_COLOR);
	m_world.render(&m_window);
	m_window.display();
}

// ----------------------------------------------------------------------
// Shutdown the Application
// ----------------------------------------------------------------------

void Atrium::shutdown()
{
	m_window.close();
}