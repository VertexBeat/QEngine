#include "Tile.hpp"
#include "Globals.hpp"
#include <iostream>

// INSTRUCTIONS!!!!

// ---------------------------------------------
// --> create tile with pixel boundaries
// --> Init box2d, if m_Collision == "true"
// -> update box2d in game-loop
// -> use render() to display sprites
// ---------------------------------------------

#define DEGTORAD 0.0174532925199432957f
#define RADTODEG 57.295779513082320876f

// 1280px * 640px
// 10 * 5
#define BOX2D_CONVERTER 128.f

// calling BoxObject constructor with arguments
// all floats should be passed in meters
Tile::Tile(float positionX, float positionY, float width, float height,bool collision)
{
	m_Collision = collision;
	if (m_Collision == true) {
		m_b2Position.x = positionX + width / 2;
		m_b2Position.y = positionY - height / 2;
		m_b2Dimension.x = width;
		m_b2Dimension.y = height;
	}
	else {
		m_b2Position.x = positionX;
		m_b2Position.y = positionY;
		m_b2Dimension.x = width;
		m_b2Dimension.y = height;
		m_Collision = collision;
	}
}

Tile::Tile()
{
	m_b2Position.x = 800.f;
	m_b2Position.y = 0;
	m_b2Dimension.x = 64.f;
	m_b2Dimension.y = 64.f;
	m_Collision = false;
}


Tile::~Tile()
{
}
//----------------------------------

// load sprite textures
void Tile::loadTexture(std::string id, std::string filePath)
{
	m_filePath = id;
	// loads texture from filePath and puts it into TextureManager with key = id
	g_pTextureManager->AddTexture(id, filePath);
	std::cout << "TileLoader added Texture with id " << id << std::endl;

	// get texture and create tile as sprite for beeing rendered
	const sf::Texture& texture = g_pTextureManager->GetTexture(id);
	m_sprite.setTexture(texture);
}
//----------------------------------

// load sprite textures
void Tile::loadTexture(const sf::Texture& texture)
{
	m_sprite.setTexture(texture);
}
//----------------------------------

// if m_Collision is true init Box2D!
void Tile::InitBox2d()
{
	float boxPositionX = m_b2Position.x / BOX2D_CONVERTER;
	float boxPositionY = m_b2Position.y / BOX2D_CONVERTER;
	float boxWidth = m_b2Dimension.x / BOX2D_CONVERTER;
	float boxHeight = m_b2Dimension.y / BOX2D_CONVERTER;
	m_Box2d = BoxObject(boxPositionX, boxPositionY, boxWidth, boxHeight, m_Type);

}
//----------------------------------

// set collision-type
void Tile::setType(BODYTYPE type)
{
	m_Type = type;
}
//----------------------------------

// get updated Box2d coordinates and rotation 
// convert them into coordinates to display sprites properly
void Tile::updateBox2d()
{
	m_Box2d.update();
	m_b2Position.x = m_Box2d.getPosition().x * BOX2D_CONVERTER;
	m_b2Position.y = m_Box2d.getPosition().y * BOX2D_CONVERTER;
	m_b2Dimension.x = m_Box2d.getDimension().x * BOX2D_CONVERTER;
	m_b2Dimension.y = m_Box2d.getDimension().y * BOX2D_CONVERTER;
	m_angle = m_Box2d.getAngle();
}
//----------------------------------

// set collision to "true" if object should be handled as box2d-object
void Tile::setCollision(bool collision)
{
	m_Collision = collision;
}

// render sprite 
sf::Sprite Tile::render()
{
	m_sprite.setOrigin(m_b2Dimension.x / 2.f, m_b2Dimension.y / 2.f);
	if (m_Collision == true) {
		updateBox2d();
		m_sprite.setPosition(m_b2Position.x, m_b2Position.y);
		m_sprite.setRotation(m_Box2d.getAngle() * RADTODEG);
	}
	else {
		m_sprite.setPosition(m_b2Position.x + m_b2Dimension.x / 2, m_b2Position.y - m_b2Dimension.y / 2);
	}
	return m_sprite;
}
void Tile::setBox2dConverter(float conversionRate)
{
	m_box2dPixelConversion = conversionRate;
}
//----------------------------------
