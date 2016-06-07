#include "EntityManager.hpp"
#include <assert.h>


EntityManager::EntityManager()
{
}


EntityManager::~EntityManager()
{
}


int EntityManager::addEntity(std::unique_ptr<Entity> gameObject)
{
	int size = m_EntityManager.size();
	gameObject->setID(size);
	// add entity-object to EntityManager and increment entity_id;
	m_EntityManager.insert(std::make_pair(size, std::move(gameObject)));
	std::cout << "Entity added! " << m_EntityManager.size() << std::endl;
	m_nEntityCounter ++;
	return size;
}



void EntityManager::killEntity(int entityId)
{
	std::map<int, std::unique_ptr<Entity>>::iterator it = m_EntityManager.find(entityId);

	if (it != m_EntityManager.end())
	{
		m_EntityManager.erase(it);
	}
	else
		std::cout << "Couldn`t kill Entity with id: " << entityId << " , because there is no Entity with this id in EntityManager" << std::endl;
}



static std::unique_ptr<Entity> EmptyEntity;

Entity* EntityManager::getEntity(int entityId)
{
	std::map<int, std::unique_ptr<Entity>>::iterator it = m_EntityManager.find(entityId);
	if (it != m_EntityManager.end())
	{
		if (it->second != nullptr)
		{
			std::cout << "GEt: " << it->second.get() << std::endl;
			return it->second.get();
		}
		else
		{
			std::cout << "Pointer to object is invalid!" << std::endl;
			return nullptr;
		}
	}
	else 
	{
		std::cout << "Couldn`t find Entity with id: " << entityId << " in EntityManager" << std::endl;
		return nullptr;
	}
		
}

