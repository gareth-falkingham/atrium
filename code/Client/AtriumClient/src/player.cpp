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
	sf::Image texImage;
	texImage.create(Const::PLAYER_FRAME_WIDTH * 2, Const::PLAYER_FRAME_COUNT * Const::PLAYER_FRAME_HEIGHT);

	// draw the 4 frames of body into the texture and mirror as well
	texImage.copy(bodyImage, 0, 0);
	bodyImage.flipHorizontally(); // flip it
	texImage.copy(bodyImage, Const::PLAYER_FRAME_WIDTH, 0);
	bodyImage.flipHorizontally(); // reset it ( so that later access will be normal ? )

	int x, y;
	for (x = 0; x < 2; x++)
	{
		for (y = 0; y < Const::PLAYER_FRAME_COUNT; y++)
		{
			texImage.copy(headImage, x * Const::PLAYER_FRAME_WIDTH, y * Const::PLAYER_FRAME_HEIGHT, sf::IntRect(0, 0, 0, 0), true);
			texImage.copy(hairImage, x * Const::PLAYER_FRAME_WIDTH, y * Const::PLAYER_FRAME_HEIGHT, sf::IntRect(0, 0, 0, 0), true);
		}
	}

	m_texture = new sf::Texture();
	m_texture->loadFromImage(texImage);
	m_sprite = new sf::Sprite((*m_texture));
	m_sprite->setTextureRect(sf::IntRect(0, 0, Const::PLAYER_FRAME_WIDTH, Const::PLAYER_FRAME_HEIGHT));
}

// ----------------------------------------------------------------------
// Update the Player Sprite 
// ----------------------------------------------------------------------
void Player::update(float p_delta)
{
	m_position.y += Const::WORLD_GRAVITY;
	if (m_position.y >= Const::GROUND_Y){ m_position.y = Const::GROUND_Y; }
	m_sprite->setPosition(m_position);
	m_sprite->setOrigin(Const::PLAYER_FRAME_WIDTH * 0.5, Const::PLAYER_FRAME_HEIGHT * 0.5);
}

// ----------------------------------------------------------------------
// Render the Player Sprite 
// ----------------------------------------------------------------------

void Player::render(sf::RenderWindow* p_window)
{
	p_window->draw((*m_sprite));
}