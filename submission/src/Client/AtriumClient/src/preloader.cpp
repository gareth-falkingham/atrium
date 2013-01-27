#include "preloader.hpp"
#include "atrium.hpp"

Preloader::Preloader(Atrium* p_atrium)
{
	m_texture = Assets::getInstance()->getTexture("assets/images/loading.png");
	m_bgSprite = new sf::Sprite((*m_texture));
	m_atrium = p_atrium;

	m_loadingTexture = Assets::getInstance()->getTexture("assets/images/loading_text.png");
	m_continueTexture = Assets::getInstance()->getTexture("assets/images/continue_text.png");
	m_infoSprite = new sf::Sprite((*m_loadingTexture));
	m_infoSprite->setPosition(640.0f, 381.0f);
}

Preloader::~Preloader()
{
	dispose();
}

void Preloader::dispose()
{
	delete m_bgSprite;
	m_bgSprite = 0;
	delete m_infoSprite;
	m_infoSprite = 0;
//	delete m_loadingTexture;
	m_loadingTexture = 0;
//	delete m_continueTexture;
	m_continueTexture = 0;
	m_atrium = 0;
}

void Preloader::show(sf::RenderWindow* p_window)
{
	p_window->clear(Const::CLEAR_COLOR);
	p_window->draw((*m_bgSprite));
	p_window->draw((*m_infoSprite));
	p_window->display();
}

void Preloader::showContinue(sf::RenderWindow* p_window)
{
	m_infoSprite->setPosition(520.0f, 381.0f);
	m_infoSprite->setTexture((*m_continueTexture), true);
	p_window->clear(Const::CLEAR_COLOR);
	p_window->draw((*m_bgSprite));
	p_window->draw((*m_infoSprite));
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