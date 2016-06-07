#pragma once
#include "TSingleton.hpp"
#include "Entity.hpp"
#include <map>
#include <iostream>
#include <memory>

#define g_pEntityManager EntityManager::Get()

class EntityManager : public TSingleton<EntityManager>
{
public:
	EntityManager();
	~EntityManager();
	// add entity to entity-manager and returns id in entityManager
	int addEntity(std::unique_ptr<Entity> gameObject);

	// get pointer to entityManager
	//std::map<int, std::unique_ptr<Entity>> getEntityManager() { return m_EntityManager; };

	// destroy entity
	void killEntity(int entityId);

	// get entity
	Entity* getEntity(int entityId);
private:
	int m_nEntityCounter = 0;

	std::map<int, std::unique_ptr<Entity>> m_EntityManager;
};

