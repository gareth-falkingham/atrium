#include "player.hpp"

// ----------------------------------------------------------------------
// Constructor
// ----------------------------------------------------------------------

Player::Player() : WorldEntity()
{
	initializeSprite(1, 1 ,1);
}

// ----------------------------------------------------------------------
// Overloaded Constructor
// ----------------------------------------------------------------------

Player::Player(int p_head, int p_hair, int p_body) : WorldEntity()
{
	initializeSprite(p_head, p_hair, p_body);
}

// ----------------------------------------------------------------------
// Deconstructor
// ----------------------------------------------------------------------

Player::~Player(){}

// ----------------------------------------------------------------------
// Build an asset path given a type (body, head, hair etc. ) and integer
// ----------------------------------------------------------------------

std::string Player::buildAssetPath(std::string p_type, int p_ext)
{
	std::ostringstream ss;
	ss << "assets/images/";
	ss << p_type << "_";
	ss << std::setw(3) << std::setfill('0') << p_ext;
	ss << ".png";
	return ss.str();
}

// ----------------------------------------------------------------------
// Initialize the Players Texture and Sprite 
// ----------------------------------------------------------------------

void Player::initializeSprite(int p_body, int p_head, int p_hair)
{
	// load the applicable images in
	sf::Image bodyImage = *Assets::getInstance()->getImage(buildAssetPath("body", p_body));
	sf::Image headImage = *Assets::getInstance()->getImage(buildAssetPath("head", p_head));
	sf::Image hairImage = *Assets::getInstance()->getImage(buildAssetPath("hair", p_hair));

	// initialize the texture ( width * 2 to allow the flipped version )
	m_texture = new sf::Texture();
	m_texture->create(Const::PLAYER_FRAME_WIDTH * 2, Const::PLAYER_FRAME_COUNT * Const::PLAYER_FRAME_HEIGHT);

	// draw the 4 frames of body into the texture and mirror as well
	m_texture->update(bodyImage, 0, 0);
	bodyImage.flipHorizontally(); // flip it
	m_texture->update(bodyImage, Const::PLAYER_FRAME_WIDTH, 0);
	bodyImage.flipHorizontally(); // reset it ( so that later access will be normal ? )
	int x, y;
	for (x = 0; x < 2; x++)
	{
		for (y = 0; y < Const::PLAYER_FRAME_HEIGHT; y++)
		{
			m_texture->update(headImage, x, y);
			m_texture->update(hairImage, x, y);
		}
	}
	m_sprite = new sf::Sprite((*m_texture));
	m_sprite->setTextureRect(sf::IntRect(0, 0, Const::PLAYER_FRAME_WIDTH, Const::PLAYER_FRAME_HEIGHT));
}

// ----------------------------------------------------------------------
// Update the Player Sprite 
// ----------------------------------------------------------------------
void Player::update(float p_delta)
{
	m_sprite->setPosition(m_position);
}

// ----------------------------------------------------------------------
// Render the Player Sprite 
// ----------------------------------------------------------------------

void Player::render(sf::RenderWindow* p_window)
{
	p_window->draw((*m_sprite));
	sf::Sprite s((*m_texture));
	p_window->draw(s);
}