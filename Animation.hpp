#pragma once
#include "Entity.hpp"
#include <string>
#include <SFML\Graphics.hpp>
#include <map>

class Animation
{
public:
	Animation();
	~Animation();
public:
	void getSprites(std::vector<sf::Sprite> spriteCycle);
	// get sprite of animation including frame
	sf::Sprite playAnimation();
	void setPosition(sf::Vector2f position);
	void setAnimationFPS(int fps);
	int getAnimationFPS() { return m_AnimFramesPerSec; };

private:
	std::vector<sf::Sprite> m_AnimationCycle;
	sf::Sprite m_FrameSprite;
	// Which Frame is currently active and should be displayed
	int m_ActiveFrame;
	int m_Frames;
	int m_AnimFramesPerSec;
	int m_AnimationCounter;
	sf::Vector2f m_Position;
};

