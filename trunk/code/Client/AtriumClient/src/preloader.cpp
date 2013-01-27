#include "preloader.hpp"
#include "atrium.hpp"

Preloader::Preloader(Atrium* p_atrium)
{
	m_texture = Assets::getInstance()->getTexture("assets/images/loading.png");
	m_sprite = new sf::Sprite((*m_texture));
}

Preloader::~Preloader()
{
	delete m_texture;
	m_texture = 0;
	delete m_sprite;
	m_sprite = 0;
	//m_atrium = 0;
}

void Preloader::dispose()
{
	delete m_texture;
	m_texture = 0;
	delete m_sprite;
	m_sprite = 0;
	//m_atrium = 0;
}

void Preloader::show()
{
	//m_atrium->window()->clear(Const::CLEAR_COLOR);
	//	m_atrium->window()->draw((*m_sprite));
	//m_atrium->window()->display();
}

void Preloader::showContinue()
{
	m_atrium->startGame();
}