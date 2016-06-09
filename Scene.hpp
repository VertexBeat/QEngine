#pragma once
#include "Player.hpp"
#include "SFML\Graphics.hpp"
#include <vector>
#include <map>
#include "Tile.hpp"
#include "BoxObject.hpp"

class Scene
{
public:
	Scene();
	~Scene();
	//void setView(sf::Vector2f position); -> when rendering!!!
	void addTileLayerToScene(std::multimap<int,Tile> mapTiles);
	std::vector<sf::Sprite> renderSceneTiles(int positionStart, int positionEnd);
	/*
	std::vector<sf::Sprite> renderSceneObjects(int positionStart, int positionEnd);
	void createSceneColliders(int positionStart, int positionEnd);
	*/
private:
	// save all tilemaps into vector
	std::vector<std::multimap<int,Tile>> m_SceneTiles;
	// save all objects into vector
	std::vector<std::multimap<int,sf::Sprite>> m_SceneObjects;
	// save all Box2D into vector
	std::vector<std::multimap<int, BoxObject>> m_SceneColliders;
};

