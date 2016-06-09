#pragma once
#include "BoxObject.hpp"
#include <string>
#include <SFML\Graphics.hpp>
#include "TextureManager.hpp"
#include <string>

class Tile 
{
public:
	Tile(float positionX, float positionY, float width, float height,bool collision);
	Tile();
	~Tile();

	// load texture 
	void loadTexture(std::string id, std::string filePath);
	void loadTexture(const sf::Texture & texture);
	// init box2d
	void InitBox2d();
	// set Bodytype
	void setType(BODYTYPE type);
	// update box2d
	void updateBox2d();
	// set collision
	void setCollision(bool collision);
	// check collision
	bool getCollision(){ return m_Collision; };
	// render sprite
	sf::Sprite render();
	// set PixelConversion
	void setBox2dConverter(float conversionRate);
	void scale(float scaling);
	sf::Sprite getSprite() { return m_sprite; };

	// TEST-AREA!!!!
	std::string getFilePath() { return m_filePath; };
private:
	sf::Sprite m_sprite;
	BODYTYPE m_Type;
	BoxObject m_Box2d;
	b2Vec2 m_b2Position;
	b2Vec2 m_b2Dimension;
	bool m_Collision;
	float m_angle;
	float m_box2dPixelConversion;
	// just for testing purposes
	std::string m_filePath;
};

