#include "player.hpp"
#include <cassert>
#include "const.hpp"
#include "therakman.h"

float Player::sm_playerLocalX = 0.0f;
float Player::sm_playerWorldX = 0.0f;

// ----------------------------------------------------------------------
// Constructor
// ----------------------------------------------------------------------

Player::Player() : WorldEntity()
{
	m_showHeartTimer = 0.0f;
	memset(&m_playerData, 0, sizeof(m_playerData));
	m_heart.Initialise();
}

// ----------------------------------------------------------------------
// Overloaded Constructor
// ----------------------------------------------------------------------

Player::Player(int p_body, int p_head, int p_hair, int p_heart) : WorldEntity()
{
	m_showHeartTimer = 0.0f;
	memset(&m_playerData, 0, sizeof(m_playerData));
	initializeSprite(p_body, p_head, p_hair);
	m_heart.Initialise( p_heart );
}

// ----------------------------------------------------------------------
// Deconstructor
// ----------------------------------------------------------------------

Player::~Player(){}

void Player::randomiseBody()
{
	initializeSprite((rand() % Const::MAX_BODY_PIECES) + 1,
					 (rand() % Const::MAX_HEAD_PIECES) + 1,
					 (rand() % Const::MAX_HAIR_PIECES) + 1);
}

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
// Randomly generate the heart, find its texture etc
// ----------------------------------------------------------------------

void Player::generateHeart(int heartID)
{
	m_showHeartTimer = 2.0f;
	m_heart.Initialise(heartID);
	m_playerData.heartID = m_heart.getHeartID();
}

// ----------------------------------------------------------------------
// Initialize the Players Texture and Sprite 
// ----------------------------------------------------------------------

void Player::initializeSprite(int p_body, int p_head, int p_hair)
{
	// constructors share this so use it to initialize members
	m_speed = 0.0f;
	//m_localX = m_localY = 0.0f;
	m_playerState = PlayerState::STANDING;

	// load the applicable images in
	if( p_body > Const::MAX_BODY_PIECES )
		p_body = Const::MAX_BODY_PIECES-1;
	if( p_head > Const::MAX_HEAD_PIECES )
		p_head = Const::MAX_HEAD_PIECES-1;
	if( p_hair > Const::MAX_HAIR_PIECES )
		p_hair = Const::MAX_HAIR_PIECES-1;

	sf::Image bodyImage = *Assets::getInstance()->getImage(buildAssetPath("body", p_body));
	sf::Image headImage = *Assets::getInstance()->getImage(buildAssetPath("head", p_head));
	sf::Image hairImage = *Assets::getInstance()->getImage(buildAssetPath("hair", p_hair));

	m_playerData.hairID = p_hair;
	m_playerData.headID = p_head;
	m_playerData.bodyID = p_body;
	m_playerData.heartID = 1;

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

void Player::regenCharacter()
{
	delete m_animatedSprite;
	delete m_sprite;
	//delete m_texture;

	m_animatedSprite = 0;
	m_sprite = 0;
	m_texture = 0;

	randomiseBody();

}

// ----------------------------------------------------------------------
// Getter for the speed
// ----------------------------------------------------------------------

float Player::speed()
{
	return m_speed; 
}

// ----------------------------------------------------------------------
// Jump
// ----------------------------------------------------------------------

void Player::jump()
{
}

// ----------------------------------------------------------------------
// Setters for the localX and localY
// ----------------------------------------------------------------------

//void Player::localX(float p_value){ m_localX = p_value; }
//void Player::localY(float p_value){ m_localY = p_value; }

void 
Player::UpdatePosition()
{
	//blah
}

// ----------------------------------------------------------------------
// Move the Player Left 
// ----------------------------------------------------------------------

void Player::moveLeft(float fDT)
{
	if (m_facing != Direction::LEFT)
	{
		m_facing = Direction::LEFT;
		m_animatedSprite->changeAnimation("left_walk");
	}
	else { m_animatedSprite->nextFrame(); }

	m_speed -= Const::PLAYER_ACCELERATION*fDT;
	if( m_speed < -Const::PLAYER_MAX_SPEED )
	{ m_speed = -Const::PLAYER_MAX_SPEED; }
}

// ----------------------------------------------------------------------
// Move the Player Right 
// ----------------------------------------------------------------------

void Player::moveRight(float fDT)
{
	if (m_facing != Direction::RIGHT)
	{
		m_facing = Direction::RIGHT;
		m_animatedSprite->changeAnimation("right_walk");
	}
	else { m_animatedSprite->nextFrame(); }
	
	m_speed += Const::PLAYER_ACCELERATION*fDT;
	if( m_speed > Const::PLAYER_MAX_SPEED )
	{ m_speed = Const::PLAYER_MAX_SPEED; }
}

// ----------------------------------------------------------------------
// Move the Player Slowly to a stop
// ----------------------------------------------------------------------

void Player::moveNone(float fDT)
{
	m_facing = Direction::NONE;
	m_speed -= m_speed*fDT * 10.0f; //Friction

	switch(m_facing)
	{
		case Direction::LEFT: 
		{
			if (m_speed >= 0.0f)
			{
				m_speed = 0.0f;
				m_animatedSprite->changeAnimation("left_stand");
				
			}
			else
			{
			}
			break;
		}
		case Direction::RIGHT: 
		{
			if (m_speed <= 0.0f)
			{
				m_speed = 0.0f;
				m_animatedSprite->changeAnimation("right_stand");
				m_facing = Direction::NONE;
			}
			else
			{
			}
			break;
		}
	}
}

// ----------------------------------------------------------------------
// Update the Player Sprite 
// ----------------------------------------------------------------------

void Player::update(float p_delta)
{
	//Debug::log(LogLevel::INFO, "Player::Update()", "X: %f, speed:%f", m_playerData.x, m_speed);
	if( m_playerData.isInteracting )
	{
		m_fInteractionTime += p_delta;
	}
	else
	{
		m_fInteractionTime = 0.0f;
	}

	m_showHeartTimer -= p_delta;
	if( m_showHeartTimer < 0.0f )
	{
		m_showHeartTimer = 0.0f;
	}

	m_playerData.x += m_speed*p_delta;
	m_heart.SetPlayerPosition( m_playerData.x, m_playerData.y );

	m_animatedSprite->update(p_delta);
	//m_localY += Const::WORLD_GRAVITY;
	m_playerData.y += Const::WORLD_GRAVITY;
	if (m_playerData.y >= Const::GROUND_Y){ m_playerData.y = m_playerData.y = Const::GROUND_Y; }

	if( TheRakMan::Get().IsPrimaryPlayer( m_playerData.playerID ) )
	{
		//sm_playerLocalX = m_localX;
		sm_playerWorldX = m_playerData.x;
		//m_sprite->setPosition( sf::Vector2f( m_localX, m_localY ) );
	}
	else
	{
		//Debug::log(LogLevel::INFO, "update", "diff in worldX:%f", (m_playerData.x-sm_playerWorldX) );
		//Debug::log(LogLevel::INFO, "update", "diff in worldX:%f", (m_playerData.x-sm_playerWorldX) );
		//m_sprite->setPosition( (400.0f)+(m_playerData.x-sm_playerWorldX), m_localY );
	}
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

	if( m_playerData.isInteracting == 1 || m_showHeartTimer > 0.0f)
	{
		m_heart.Draw( p_window );
	}
}