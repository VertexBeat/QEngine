#pragma once
#include "Entity.hpp"
#include <SFML\Graphics.hpp>
#include <string>
#include <map>
#include "World.hpp"
#include "Tile.hpp"
#include "tinyxml2.h"
#include "Animation.hpp"
#include "BoxObject.hpp"

class Player : public Entity
{
public:
	// initiates player with controller id to identify, which controls he uses!
	Player(int controllerId);
	Player(float x, float y);
	Player();
	~Player();
public:
	void move(float movement);
	void jump();
	void update();
public:
	// add animation in _playerStateMap
	// 
	void addSpriteSheet(const char* filePathConfig);

	void InitBox2d();

	void updateBox2d();

	void AddAnimation(std::string state, int nStart, int nFrames);

	// load Animation
	void loadState(std::string state);

	// play loaded Animation
	sf::Sprite play();

	void setAsBox(float x, float y);

private:
	// load spriteSheet
	// filePathImg -> load .PNG ImageSheet
	// filePathConfig -> load XML-Animation-Config
	// load into textureManager

	// map of states
	std::map<std::string, Animation> m_AnimationMap;
	std::vector<sf::Sprite> m_SpriteVec;
	// position of Player on Map
	sf::Vector2f m_Position;
	sf::Vector2f m_BoxDimension;
	float m_Angle;
	// Velocity of Player
	sf::Vector2f m_Movement; // =?
	BoxObject m_Box2d;
	BODYTYPE m_Type;
	//Animation _animation;
	sf::Sprite m_Sprite;
	Animation m_LoadedAnimation;
	const sf::Texture* m_pSpriteSheetTexture;
	tinyxml2::XMLDocument m_Doc;
	int m_ControllerId;
};

