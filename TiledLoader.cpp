#include "TiledLoader.hpp"
#include "TextureManager.hpp"
#include <iostream>




TiledLoader::TiledLoader()
{
}


TiledLoader::~TiledLoader()
{
}

void TiledLoader::loadLevel(const char * fileName)
{
	if (!m_Doc.LoadFile(fileName))
	{
		// if file is found, ... proceed
		printf("load file=[%s] succeeded\n", fileName);
		// get tile-dimension for rendering
		getTileDimension();
		//load all textures into TextureManager
		loadMapTextures();
	}
	else
	{
		printf("load file=[%s] failed\n", fileName);
	}
}

void TiledLoader::setScrollDirection(SCROLLDIRECTION direction)
{
	m_ScrollDirection = direction;
}

std::multimap<int, Tile> TiledLoader::saveAsTileLayer(const char* layerName)
{
	tinyxml2::XMLElement* layer = m_Doc.FirstChildElement()->FirstChildElement("layer");
	std::multimap<int, Tile> map;

	for (tinyxml2::XMLElement* e = layer; e != NULL; e = e->NextSiblingElement("layer"))
	{
		// get number of tiles in x-row
		const char* layerX = nullptr;
		layerX = e->Attribute("width");
		int nWidth = atoi(layerX);

		// get number of tiles in y-row
		const char* layerY = nullptr;
		layerY = e->Attribute("height");
		int nHeight = atoi(layerX);

		const char* name = nullptr;
		name = e->Attribute("name");

		if (*name == *layerName)
		{
			int rowCounter = 0;
			int columnCounter = 0;
			int rowVerifier;
			int counter = 0;
			// nHeight, nWidth
			for (tinyxml2::XMLElement* f = layer->FirstChildElement("data")->FirstChildElement("tile"); f != NULL; f = f->NextSiblingElement("tile")) 
			{
				// get id for current tile-item
				const char* gid = nullptr;
				gid = f->Attribute("gid");
				int id = atoi(gid);

				// map-tile-sorting-logic
				if (rowCounter < nWidth) {
					// init tile with position/dimension and bind texture to it`s sprite
					int posX = rowCounter * m_TileWidth;
					int posY = columnCounter * m_TileHeight;
					Tile tmpTile(posX, posY, m_TileWidth, m_TileHeight, false);
					std::cout << "Counter: " << counter << "X: " << posX << ", Y: " << posY << std::endl;
					counter++;
					tmpTile.loadTexture(getGidTexture(id));

					// insert and sort tiles
					if (m_ScrollDirection == x)
					{
						map.insert(std::make_pair(posX, tmpTile));
					} else {
						map.insert(std::make_pair(posY, tmpTile));
					}

					// modify Counter, map is working properly (not be able to use for-loop in this case -> solution with if-else necessaary)
					rowVerifier = rowCounter + 1;
					if (rowVerifier < nWidth) {
						rowCounter++;
					}
				}
				else {
					rowCounter = 0;
					columnCounter++;
				}
			}
		} else {
			std::cout << "Not workin!" << std::endl;
		}
		std::string nameS = layerName;
		std::cout << "TileLayer[" << nameS << "] loaded!" << std::endl;
		std::cout << "Map-Size: " << map.size() << std::endl;
		return map;
	}

	return std::multimap<int, Tile>();
}

std::multimap<int, sf::Sprite> TiledLoader::saveAsObjectLayer(std::string layerName)
{
	tinyxml2::XMLElement* layer = m_Doc.FirstChildElement()->FirstChildElement("objectgroup");
	std::multimap<int, sf::Sprite> map;

	for (tinyxml2::XMLElement* e = layer; e != NULL; e = e->NextSiblingElement("objectgroup"))
	{
		if (e->Attribute("name") == layerName)
		{
			std::string objName;
			for (tinyxml2::XMLElement* e = m_Doc.FirstChildElement()->FirstChildElement("objectgroup"); e != NULL; e = e->NextSiblingElement("objectgroup"))
			{
				const char* objectGroupName = nullptr;
				objectGroupName = e->Attribute("name");
				objName = objectGroupName;

				for (tinyxml2::XMLElement* f = e->FirstChildElement("object"); f != NULL; f = f->NextSiblingElement("object"))
				{
					// Get GameObjectId (gid)
					const char* objectId = nullptr;
					objectId = f->Attribute("gid");
					int tmpGid = atoi(objectId);

					const char* id = nullptr;
					id = f->Attribute("id");
					int tmpId = atoi(id);


					// Get object-type
					const char* type = nullptr;
					type = f->Attribute("type");
					if (type != NULL) {
						std::string sType(type);
					}
					else {
					}

					const char* widthValue = nullptr;
					widthValue = f->Attribute("width");
					int nWidth = atoi(widthValue);
					float fWidth = static_cast<float>(nWidth);

					const char* heightValue = nullptr;
					heightValue = f->Attribute("height");
					int nHeight = atoi(heightValue);
					float fHeight = static_cast<float>(nHeight);

					const char* xValue = nullptr;
					xValue = f->Attribute("x");
					int nPosX = atoi(xValue);
					float fPosX = static_cast<float>(nPosX);

					const char* yValue = nullptr;
					yValue = f->Attribute("y");
					int nPosY = atoi(yValue);
					float fPosY = static_cast<float>(nPosY);

					sf::Sprite tmpSprite;
					tmpSprite.setPosition(fPosX, fPosY);
					tmpSprite.setTexture(getGidTexture(tmpGid));
					if (m_ScrollDirection == x)
					{
						map.insert(std::make_pair(fPosX, tmpSprite));
					}
					else {
						map.insert(std::make_pair(fPosY, tmpSprite));
					}

					std::string name = layerName;
					std::cout << "ObjectLayer[" + name + "] loaded!" << std::endl;
					return map;
				}
			}
		}
	}
}

void TiledLoader::getTileDimension()
{
	const char* width = nullptr;
	width = m_Doc.FirstChildElement()->Attribute("tilewidth");
	m_TileWidth = atoi(width);

	const char* height = nullptr;
	height = m_Doc.FirstChildElement()->Attribute("tileheight");
	m_TileHeight = atoi(height);
}

const sf::Texture& TiledLoader::getGidTexture(int gid)
{
	int nTextureFinder = gid;
	std::map<int, std::string>::iterator i = m_TextureIdentificationMap.find(nTextureFinder);
	std::string resultTag;
	if (i == m_TextureIdentificationMap.end()) {
		//not found
	}
	else {
		// found
		resultTag = i->second;
	}

	std::map<std::string, std::string>::iterator it = m_AssetMap.find(resultTag);
	std::string resultPath;
	if (it == m_AssetMap.end()) {
		//not found
	}
	else {
		// found
		resultPath = it->second;
		//std::cout << "load Texture=[" + resultPath + "] succeeded\n" << std::endl;
	}

	return g_pTextureManager->GetTexture(resultTag);
}

void TiledLoader::loadMapTextures()
{
	for (tinyxml2::XMLElement* e = m_Doc.FirstChildElement()->FirstChildElement("tileset")->FirstChildElement("tile"); e != NULL; e = e->NextSiblingElement("tile"))
	{

		// get tile id for textureManagement
		const char* tagId = nullptr;
		tagId = e->Attribute("id");
		tagId++;
		// tile-ids starting with 1, not zero! So tile-id matching is possible!
		// --------------------------------

		// get all available filepaths for textures
		tinyxml2::XMLElement *source = nullptr;
		source = e->FirstChildElement("image");
		const char* sourceValue = nullptr;
		sourceValue = source->Attribute("source");
		// --------------------------------------

		// Get Id of fileSource
		std::string s = "";
		s = sourceValue;
		std::string delimiter = "/";
		std::vector<std::string> fileIds;

		size_t pos = 0;
		std::string token;
		while ((pos = s.find(delimiter)) != std::string::npos) {
			token = s.substr(0, pos);
			fileIds.push_back(token);
			s.erase(0, pos + delimiter.length());
		}
		// ---------------------

		// save the results in strings and int
		std::string sSource = sourceValue;
		std::string sTextureId = s;
		int id = atoi(tagId);
		// ----------------------------------



		// create maps and insert data
		m_AssetMap.insert(std::make_pair(sTextureId, sSource));
		m_TextureIdentificationMap.insert(std::make_pair(id, sTextureId));
		g_pTextureManager->AddTexture(sTextureId, sSource);
	}
}


