#pragma once
#include <vector>
#include "Tile.hpp"
#include "TSingleton.hpp"
#include "tinyxml2.h"
#include "Tile.hpp"
#include <SFML\Graphics.hpp>
#define g_pTiledLoader TiledLoader::Get()
/*
 Guide:
 1) loadLevel and getLayers
 2) define scrollDirection
 3) define each layer as (Tile,Object,PhysX)
 4) each layer-method will return an ordered multimap
 5) save them as World in g_pWorld (order defines drawing-order, background <- tilemaps <- object_maps <- physX ... first item gets first drawn)
 6) RenderScene in World for sf::View and Scrolldirection as parameter -> find all objects in map <= x and renders them to the view
 */


class TiledLoader : public TSingleton<TiledLoader>
{
public:
	TiledLoader();
	~TiledLoader();

	enum SCROLLDIRECTION
	{
		x,
		y
	};

	// loads tmx-file into m_Doc
	void loadLevel(const char* fileName);
	void loadLevel(const char* fileName, float scaling);

	// set the scrolldirection(it defines, how the multimaps of the layers get ordered)
	void setScrollDirection(SCROLLDIRECTION direction);

	// returns tile-map (int = scrolldirection)
	std::multimap<int,Tile> saveAsTileLayer(const char* layerName);

	// returns multimap of sprites
	std::multimap<int,sf::Sprite> saveAsObjectLayer(std::string layerName);

	// returns box2d multimap with static box2d-objects for physX
	//std::multimap<int,BoxObject> saveAsPhysXLayer(std::string layerName);
private:
	//map
	void rescale(float scaling);
	int m_TileWidth;
	int m_TileHeight;
	void getTileDimension();
	// get Texture of gid
	const sf::Texture& getGidTexture(int gid);

	// load Textures
	void loadMapTextures();
	tinyxml2::XMLDocument m_Doc;

	SCROLLDIRECTION m_ScrollDirection;

	// Texture-Save/Search-Container
	std::map<std::string, std::string> m_AssetMap;
	std::map<int, std::string> m_TextureIdentificationMap;
};

