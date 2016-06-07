#pragma once
#include "Entity.hpp"
#include <Box2D\Box2D.h>

enum BODYTYPE {dynamicBody,staticBody,kinematicBody};

class BoxObject : public Entity
{
public:
	BoxObject();
	BoxObject(float positionX, float positionY, float width, float height, BODYTYPE type);
	b2Vec2 getPosition();
	void setPosition(b2Vec2 position);
	b2Body* getBody() { return m_body; };
	b2Vec2 getDimension();
	float getAngle();
	void update();
	~BoxObject();
protected:
	// position of the game-object in meters
	b2Vec2 m_b2Position;
	b2Vec2 m_b2SpritePosition;
	b2Vec2 m_b2SpriteDimension;
	float m_angle;
	// size of the game-object in meters
	b2Vec2 m_b2Dimension;

	b2Body* m_body;
	void Init(BODYTYPE type);
};

