#include "BoxObject.hpp"
#include "World.hpp"
#include <iostream>

#define DEGTORAD 0.0174532925199432957f
#define RADTODEG 57.295779513082320876f

// constructor without parameters
BoxObject::BoxObject()
{
	// set position and dimension
	b2Vec2 m_b2Position(5, 5);
	b2Vec2 m_b2Dimension(1, 1);

	// init box2d object
	Init(BODYTYPE::staticBody);
}
// ----------------------------

// constructor with parameters
BoxObject::BoxObject(float positionX, float positionY, float width, float height, BODYTYPE type)
{
	// set position
	m_b2Position.x = positionX;
	m_b2Position.y = positionY;

	// set dimension
	m_b2Dimension.x = width;
	m_b2Dimension.y = height;

	// init box2d with type
	Init(type);
}
// ----------------------------

// return box2D-position
b2Vec2 BoxObject::getPosition()
{
	return m_b2Position;
}
// ----------------------------

// set box2d position
void BoxObject::setPosition(b2Vec2 position)
{
	b2Vec2 vPosition;
	vPosition.x = position.x;
	vPosition.y = m_b2Position.y;
	m_body->SetTransform(vPosition, 0 * DEGTORAD);
}
// ----------------------------

// getbox2d dimension
b2Vec2 BoxObject::getDimension()
{
	return m_b2Dimension;
}
// ----------------------------

// get angle
float BoxObject::getAngle()
{
	return m_angle;
}
// ----------------------------

// update physics
void BoxObject::update()
{
	m_b2Position.x = m_body->GetPosition().x;
	m_b2Position.y = m_body->GetPosition().y;
	m_angle = m_body->GetAngle();
}
// ----------------------------

// destructor
BoxObject::~BoxObject()
{
}
// ----------------------------

// initialization of box2d
void BoxObject::Init(BODYTYPE type)
{
	// set body definition
	b2BodyDef bodyDef;
	bodyDef.position.Set(m_b2Position.x, m_b2Position.y);

	// save body in world

	// switch bodyDef.type on type
	switch (type)
	{
	case BODYTYPE::dynamicBody:
		bodyDef.type = b2_dynamicBody;
		break;
	case BODYTYPE::kinematicBody:
		bodyDef.type = b2_kinematicBody;
		break;
	default:
		bodyDef.type = b2_staticBody;
		break;
	}

	m_body = g_pWorld->getWorld()->CreateBody(&bodyDef);
	m_body->SetTransform(m_b2Position, 0 * DEGTORAD);

	// create shape with dimensions
	b2PolygonShape bodyBox;
	bodyBox.SetAsBox(m_b2Dimension.x * 0.482f, m_b2Dimension.y * 0.482f);

	// create fixture
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &bodyBox;
	fixtureDef.density = 1.f;
	fixtureDef.friction = 0.3f;

	// save fixture in body
	m_body->CreateFixture(&fixtureDef);
}
// ----------------------------