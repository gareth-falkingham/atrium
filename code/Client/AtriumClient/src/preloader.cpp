#include "preloader.hpp"
#include "atrium.hpp"

Preloader::Preloader(Atrium* p_atrium)
{
	m_texture = Assets::getInstance()->getTexture("assets/images/loading.png");
	m_sprite = new sf::Sprite((*m_texture));
	m_atrium = p_atrium;

	m_font = new sf::Font();
	m_font->loadFromFile("assets/fonts/GILLUBCD.ttf");
	m_loadingText = new sf::Text("Loading...", (*m_font), 36);
	m_loadingText->setPosition(640.0f, 373.0f);
	m_loadingText->setColor(sf::Color(211, 211, 216));
	m_continueText = new sf::Text("Click to Continue", (*m_font), 36);
	m_continueText->setPosition(526.0f, 373.0f);
	m_continueText->setColor(sf::Color(211, 211, 216));
}

Preloader::~Preloader()
{
	dispose();
}

void Preloader::dispose()
{
	delete m_sprite;
	m_sprite = 0;
	m_atrium = 0;

	// this crashes stuff ??
	//delete m_loadingText;
	//m_loadingText = 0;
	//delete m_continueText;
	//m_continueText = 0;
	//delete m_font;
	//m_font = 0;
}

void Preloader::show(sf::RenderWindow* p_window)
{
	p_window->clear(Const::CLEAR_COLOR);
	p_window->draw((*m_sprite));
	p_window->draw((*m_loadingText));
	p_window->display();
}

void Preloader::showContinue(sf::RenderWindow* p_window)
{
	p_window->clear(Const::CLEAR_COLOR);
	p_window->draw((*m_sprite));
	p_window->draw((*m_continueText));
	p_window->display();

	bool clicked = false;
	sf::Event event;
	while(!clicked)
	{
		p_window->pollEvent(event);
		if (event.type == sf::Event::MouseButtonPressed)
		{
			clicked = true;
			break;
		}
	}
	m_atrium->startGame();
}