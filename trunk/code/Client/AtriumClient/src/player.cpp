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
	ss << p_type << "_";
	ss << std::setw(3) << std::setfill('0') << p_ext;
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
	m_texture.create(FRAME_WIDTH * 2, FRAMES * FRAME_HEIGHT);

	// draw the 4 frames of body into the texture and mirror as well
	m_texture.update(bodyImage, 0, 0);
	bodyImage.flipHorizontally(); // flip it
	m_texture.update(bodyImage, FRAME_WIDTH, 0);
	bodyImage.flipHorizontally(); // reset it ( so that later access will be normal ? )
	int x, y;
	for (x = 0; x < 2; x++)
	{
		for (y = 0; y < FRAME_HEIGHT; y++)
		{
			m_texture.update(headImage, x, y);
			m_texture.update(hairImage, x, y);
		}
	}
	m_sprite.setTexture(m_texture);
	m_sprite.setTextureRect(sf::IntRect(0, 0, FRAME_WIDTH, FRAME_HEIGHT));
}