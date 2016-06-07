#pragma once
#include <map>

/*
	game-object base class
*/
class Entity
{
public:
	Entity();
	int getID() { return m_nID; };
	void setID(int ID) { m_nID = ID; };
	virtual ~Entity();

protected:
	// unique id and identifier
	int m_nID;
};

