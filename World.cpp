#include "World.hpp"
#include "BoxObject.hpp"
#include "SFMLDebugDraw.hpp"
#include <Box2D\Box2D.h>



World::World()
{
	// create new box2d world with gravity enabled
	b2Vec2 gravity(0.f, 9.8f);

	m_pWorld = std::make_unique<b2World>(gravity);
	m_pWorld->SetAllowSleeping(false);
}

void World::updateGravity(int level)
{
	m_pWorld->SetGravity(b2Vec2(0, 1.5 + (level / 2.0)));
}

void World::updatePhysiX(sf::Time deltaTime)
{
	float seconds = deltaTime.asSeconds();
	m_pWorld->Step(seconds, 8, 3);
}


World::~World()
{
}

