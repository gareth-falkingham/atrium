#include "animated_sprite.h"

// ----------------------------------------------------------------------
// Default Constructor
// ----------------------------------------------------------------------

AnimatedSprite::AnimatedSprite()
{
	m_sprite = 0;
	m_currentFrame = 0;
	m_currentAnimation = 0;
	m_frameTimer = 0.0f;
}

// ----------------------------------------------------------------------
// Constructor
// ----------------------------------------------------------------------

AnimatedSprite::AnimatedSprite(sf::Sprite* p_sprite, int p_frameWidth, int p_frameHeight)
{
	m_sprite = p_sprite;
	m_currentFrame = 0;
	m_currentRect = sf::IntRect(0, 0, p_frameWidth, p_frameHeight);
	m_currentAnimation = 0;
	m_frameTimer = 0.0f;
}

// ----------------------------------------------------------------------
// Deconstructor
// ----------------------------------------------------------------------

AnimatedSprite::~AnimatedSprite()
{
	//delete m_sprite;
	m_sprite = 0;
	//delete m_currentAnimation;
	m_currentAnimation = 0;

	std::map<std::string, AnimationInfo*>::iterator i = m_animations.begin();
	for(; i != m_animations.end(); ++i )
	{
		//m_animations.erase(i);
		delete i->second;
		i->second = 0;
	}
	m_animations.clear();
}

// ----------------------------------------------------------------------
// Register an Animation
// ----------------------------------------------------------------------

void AnimatedSprite::registerAnimation(std::string p_tag, int p_xOffset, int p_yOffset, int p_frameCount, float p_frameTime, bool p_default)
{
	AnimationInfo* ai = new AnimationInfo();
	ai->frameCount = p_frameCount;
	ai->xOffset = p_xOffset;
	ai->yOffset = p_yOffset;
	ai->frameTime = p_frameTime;
	m_animations[p_tag] = ai;
	if (p_default){ changeAnimation(p_tag); }
}

// ----------------------------------------------------------------------
// Change Animation
// ----------------------------------------------------------------------

void AnimatedSprite::changeAnimation(std::string p_tag)
{
	m_currentFrame = 0;
	m_currentAnimation = m_animations[p_tag];
	nextFrame(0);
}

// ----------------------------------------------------------------------
// Move onto the Next Frame
// ----------------------------------------------------------------------

void AnimatedSprite::nextFrame(int p_overrideFrame)
{
	//Debug::log(LogLevel::INFO, "nextFrame", "%f of %f", m_frameTimer, m_currentAnimation->frameTime);
	if (p_overrideFrame == -1 && (m_frameTimer >= m_currentAnimation->frameTime))
	{
		m_frameTimer = 0.0f;
		if (m_currentFrame >= m_currentAnimation->frameCount){ m_currentFrame = 0; }
		else { m_currentFrame++; }
	}
	m_currentRect.left = m_currentAnimation->xOffset;
	m_currentRect.top = m_currentAnimation->yOffset * m_currentFrame;
	m_sprite->setTextureRect(m_currentRect);
}

// ----------------------------------------------------------------------
// Update function
// ----------------------------------------------------------------------

void AnimatedSprite::update(float p_delta)
{
	m_frameTimer += p_delta;
}