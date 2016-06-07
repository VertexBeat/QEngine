#pragma once
#include <vector>
#include "Tile.hpp"
#include "TSingleton.hpp"
#include "tinyxml2.h"
#define g_pTiledManager TiledManager::Get()

class TiledManager : public TSingleton<TiledManager>
{

public:
	TiledManager();
	~TiledManager();

	// loads tmx-file
	std::vector<Tile> loadLevel(const char* fileName);

private:
	tinyxml2::XMLDocument m_Doc;
	std::map<std::string, std::string> m_AssetMap;
	std::map<int, std::string> m_TextureIdentificationMap;

	std::vector<Tile> m_TileVec;
};

