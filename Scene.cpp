#include "Scene.hpp"



Scene::Scene()
{
}


Scene::~Scene()
{
}

void Scene::addTileLayerToScene(std::multimap<int, Tile> mapTiles)
{

	m_SceneTiles.push_back(mapTiles);
}

std::vector<sf::Sprite> Scene::renderSceneTiles(int positionStart, int positionEnd)
{
	std::vector<sf::Sprite> vecTiles;
	for (int i = 0; i < m_SceneTiles.size(); i++) {
		for (std::multimap<int, Tile>::iterator it = m_SceneTiles[i].begin(); it != m_SceneTiles[i].end(); it++) {
			if (it->first >= positionStart && it->first <= positionEnd) {
				vecTiles.push_back(it->second.render());
			}
		}
	}
	return vecTiles;
}
/*

std::vector<sf::Sprite> Scene::renderSceneObjects(int positionStart, int positionEnd)
{
	return std::vector<sf::Sprite>();
}

void Scene::createSceneColliders(int positionStart, int positionEnd)
{
}
*/

