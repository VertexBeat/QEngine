#include "Animation.hpp"
#include "TextureManager.hpp"
#include <SFML\Graphics.hpp>
#include <fstream>
#include <iostream>
#include <sstream>
#include "World.hpp"



Animation::Animation()
{
	// Frame one is 0, because of ector-architecture
	m_ActiveFrame = 0;

	// AnimationSpeedmodifier
	m_AnimFramesPerSec = 5; // 1AnimPerSec = 60 Game fps/ 60
	m_AnimationCounter = 0;
}

Animation::~Animation()
{
}

void Animation::getSprites(std::vector<sf::Sprite> spriteCycle)
{
	m_AnimationCycle = spriteCycle;
	m_Frames = m_AnimationCycle.size();
}

sf::Sprite Animation::playAnimation()
{
	if (m_ActiveFrame >= m_AnimationCycle.size())
		m_ActiveFrame = 0;

		m_FrameSprite = m_AnimationCycle[m_ActiveFrame];
		m_FrameSprite.setPosition(m_Position);

	if (m_AnimationCounter >= m_AnimFramesPerSec) {
		m_ActiveFrame++;
		m_AnimationCounter = 0;
	}
	m_AnimationCounter++;
	return m_FrameSprite;
}

void Animation::setPosition(sf::Vector2f position)
{
	m_Position = position;
}

void Animation::setAnimationFPS(int fps)
{
	m_AnimFramesPerSec = fps;
}
