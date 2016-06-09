#pragma once
#include "TSingleton.hpp"
#include "Scene.hpp"
#include <Box2D\Box2D.h>

#define g_pWorld World::Get()
class Scene; // why?!?! forward declaration

class World : public TSingleton<World>
{
public:
	World();
	~World();
	void updateGravity(int level);
	void updatePhysiX(sf::Time deltaTime);
	void loadScene(Scene* scene);
	Scene* getScene() { return m_pScene; };
	b2World* getWorld() { return m_pWorld.get(); };
private:
	std::unique_ptr<b2World> m_pWorld;
	Scene* m_pScene;	
};

