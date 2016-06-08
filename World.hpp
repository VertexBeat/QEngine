#pragma once
#include "TSingleton.hpp"
#include <Box2D\Box2D.h>
#include <SFML/Graphics.hpp>

#define g_pWorld World::Get()

class World : public TSingleton<World>
{
public:
	World();
	void updateGravity(int level);
	void updatePhysiX(sf::Time deltaTime);
	~World();
	b2World* getWorld() { return m_pWorld.get(); };
private:
	std::unique_ptr<b2World> m_pWorld;
};

