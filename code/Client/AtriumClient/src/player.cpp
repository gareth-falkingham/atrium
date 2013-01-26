#include "player.hpp"
#include <cassert>

// ----------------------------------------------------------------------
// Constructor
// ----------------------------------------------------------------------

Player::Player() : WorldEntity()
{
	m_playerData.hairID = 1;
	m_playerData.headID = 1;
	m_playerData.bodyID = 1;
	m_playerData.heartID = 1;
	initializeSprite(m_playerData.bodyID, m_playerData.headID ,m_playerData.hairID);
}

// ----------------------------------------------------------------------
// Overloaded Constructor
// ----------------------------------------------------------------------

Player::Player(int p_body, int p_head, int p_hair) : WorldEntity()
{
	m_playerData.hairID = p_hair;
	m_playerData.headID = p_head;
	m_playerData.bodyID = p_body;
	m_playerData.heartID = 1;
	initializeSprite(m_playerData.bodyID, m_playerData.headID, m_playerData.hairID);
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
	// constructors share this so use it to initialize members
	m_speed = 0.0f;
	m_playerState = PlayerState::STANDING;

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

	// right is default, flip the images
	headImage.flipHorizontally();
	hairImage.flipHorizontally();

	int x, y;
	for (x = 0; x < 2; x++)
	{
		// if on the second row, flip the head/hair images
		if (x == 1)
		{
			headImage.flipHorizontally();
			hairImage.flipHorizontally();
		}
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
	
	m_animatedSprite = new AnimatedSprite(m_sprite, Const::PLAYER_FRAME_WIDTH, Const::PLAYER_FRAME_HEIGHT);
	m_animatedSprite->registerAnimation("left_stand", 0, 0, 1, 0, true);
	m_animatedSprite->registerAnimation("right_stand", Const::PLAYER_FRAME_WIDTH, 0, 1, 0);
	m_animatedSprite->registerAnimation("left_walk", 0, Const::PLAYER_FRAME_HEIGHT, 2, 0.2f);
	m_animatedSprite->registerAnimation("right_walk", Const::PLAYER_FRAME_WIDTH, Const::PLAYER_FRAME_HEIGHT, 2, 0.2f);
	m_animatedSprite->registerAnimation("left_jump", 0, Const::PLAYER_FRAME_HEIGHT * 3, 1, 0);
	m_animatedSprite->registerAnimation("right_jump", Const::PLAYER_FRAME_WIDTH, Const::PLAYER_FRAME_HEIGHT * 3, 1, 0);
}

// ----------------------------------------------------------------------
// Jump
// ----------------------------------------------------------------------

void Player::jump()
{
	if (m_playerState != PlayerState::JUMPING)
	{
		m_playerState = PlayerState::JUMPING;

	}
}

// ----------------------------------------------------------------------
// Move the Player Left 
// ----------------------------------------------------------------------

void Player::moveLeft()
{
	if (m_facing != Direction::LEFT)
	{
		m_facing = Direction::LEFT;
		m_animatedSprite->changeAnimation("left_walk");
	}
	else { m_animatedSprite->nextFrame(); }
	m_speed += Const::PLAYER_ACCELERATION;
	m_speed = std::min(m_speed, Const::PLAYER_MAX_SPEED);
	m_playerData.x -= m_speed;
}

// ----------------------------------------------------------------------
// Move the Player Right 
// ----------------------------------------------------------------------

void Player::moveRight()
{
	if (m_facing != Direction::RIGHT)
	{
		m_facing = Direction::RIGHT;
		m_animatedSprite->changeAnimation("right_walk");
	}
	else { m_animatedSprite->nextFrame(); }
	m_speed += Const::PLAYER_ACCELERATION;
	m_speed = std::min(m_speed, Const::PLAYER_MAX_SPEED);
	m_playerData.x += m_speed;
}

// ----------------------------------------------------------------------
// Move the Player Slowly to a stop
// ----------------------------------------------------------------------

void Player::moveNone()
{
	m_speed = 0.0f;
	switch(m_facing)
	{
		case Direction::LEFT: m_animatedSprite->changeAnimation("left_stand"); break;
		case Direction::RIGHT: m_animatedSprite->changeAnimation("right_stand"); break;
	}
	m_facing = Direction::NONE;
}

// ----------------------------------------------------------------------
// Update the Player Sprite 
// ----------------------------------------------------------------------

void Player::update(float p_delta)
{
	m_animatedSprite->update(p_delta);
	m_playerData.y += Const::WORLD_GRAVITY;
	if (m_playerData.y >= Const::GROUND_Y){ m_playerData.y = Const::GROUND_Y; }
	m_sprite->setPosition( sf::Vector2f( m_playerData.x, m_playerData.y ) );
	m_sprite->setOrigin(Const::PLAYER_FRAME_WIDTH * 0.5, Const::PLAYER_FRAME_HEIGHT * 0.5);

	//RELIES on StoreOldData being called. Compares the old data with the current data and sends any changes to the server.
	SendNewData();
	StoreOldData();
}

// ----------------------------------------------------------------------
// Render the Player Sprite 
// ----------------------------------------------------------------------

void Player::render(sf::RenderWindow* p_window)
{
	p_window->draw((*m_sprite));
}