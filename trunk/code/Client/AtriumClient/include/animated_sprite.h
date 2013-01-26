#ifndef ANIMATED_SPRITE_HPP
#define ANIMATED_SPRITE_HPP

#pragma once

#include <SFML/Graphics.hpp>
#include "debug.hpp"
#include "const.hpp"

struct AnimationInfo
{
	public:
		unsigned short frameCount;
		int xOffset;
		int yOffset;
		float frameTime;
};

class AnimatedSprite
{
	private:

		std::map<std::string, AnimationInfo*> m_animations;
		sf::Sprite* m_sprite;
		unsigned short m_currentFrame;
		sf::IntRect m_currentRect;
		AnimationInfo* m_currentAnimation;
		float m_frameTimer;

	public:

		AnimatedSprite();
		AnimatedSprite(sf::Sprite* m_sprite, int p_frameWidth, int p_frameHeight);
		virtual ~AnimatedSprite();
		void registerAnimation(std::string p_tag, int p_xOffset, int p_yOffset, int p_frameCount, float p_frameTime, bool p_default = false);
		void changeAnimation(std::string p_tag);
		void nextFrame(int p_overrideFrame = -1);
		void update(float p_delta);
};

#endif