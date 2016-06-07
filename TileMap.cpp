#include "TileMap.hpp"
#include <iostream>
#include <sstream>
#include <stdlib.h>
#include "Tile.hpp"
#include <vector>
#include "World.hpp"
#include <memory>
#include <sstream>
#include <algorithm>
#include <iterator>
#include "TextureManager.hpp"



TileMap::TileMap()
{
	_nTileHeight = 70;
	_nTileWidth = 70;
	_orientation = Orientation::orthogonal;
	_renderOrder = RenderOrder::leftdown;
	_format = Format::png;
	_layer = Layer::layer1;
}

TileMap::TileMap(int nTileHeight, int nTileWidth, Orientation orientation, RenderOrder renderOrder, Format format, Layer layer)
{
	_nTileHeight = nTileHeight;
	_nTileWidth = nTileWidth;
	_orientation = orientation;
	_renderOrder = renderOrder;
	_format = format;
	_layer = layer;
}


TileMap::~TileMap()
{
}

void TileMap::Init(const char* fileName)
{
	LoadTileMap(fileName);
	bool orient = CheckOrientation(_orientation);
	bool render = CheckRenderOrder(_renderOrder);
	bool tileSize = CheckTileSize(_nTileHeight, _nTileWidth);
	//bool format = CheckFormat(_format);

	int counter = 0;
	if (orient)
		counter++;
	if(render)
		counter++;
	if(tileSize)
		counter++;

	if (counter == 3)
		std::cout << "Your Map is allowed" << std::endl;
	else
		std::cout << "One of the formats is not supported in the Map" << std::endl;
}

bool TileMap::CheckOrientation(Orientation orientation)
{
	const char* check = _doc.FirstChildElement("map")->Attribute("orientation");

	std::string resultDoc = static_cast<std::string>(check);
	std::string resultOrient;

	switch (orientation)
	{
	case(0) :
		resultOrient = "orthogonal";
		break;
	case(1) :
		resultOrient = "isometric";
		break;
	case(2) :
		resultOrient = "staggered";
		break;
	}
	if (resultOrient != resultDoc)
	{
		std::cout << resultOrient << " != " << resultDoc << std::endl;
		return false;
	}
	
	return true;
	
}

bool TileMap::CheckRenderOrder(RenderOrder renderOrder)
{
	const char* check = _doc.FirstChildElement("map")->Attribute("renderorder");

	std::string resultDoc = static_cast<std::string>(check);
	std::string resultRenderOrder;

	switch (renderOrder)
	{
	case(0) :
		resultRenderOrder = "right-down";
		break;
	case(1) :
		resultRenderOrder = "right-up";
		break;
	case(2) :
		resultRenderOrder = "left-down";
		break;
	case(3) :
		resultRenderOrder = "left-up";
		break;
	}
	if (resultRenderOrder != resultDoc)
	{
		std::cout << resultRenderOrder << " != " << resultDoc << std::endl;
		return false;
	}

	return true;
}

bool TileMap::CheckTileSize(int tileWidth, int tileHeight)
{
	const char* tilewidth = _doc.FirstChildElement("map")->Attribute("tilewidth");
	const char* tileheight = _doc.FirstChildElement("map")->Attribute("tileheight");

	std::stringstream width;
	width << tilewidth;
	int intWidth;
	width >> intWidth;

	std::stringstream height;
	height << tileheight;
	int intHeight;
	height >> intHeight;


	if (tileWidth != intWidth)
	{
		std::cout << tileWidth << " != " << tilewidth << std::endl;
		return false;
	}
	if (tileHeight != intHeight)
	{
		std::cout << tileHeight << " != " << tileheight << std::endl;
		return false;
	}

	return true;
}


void TileMap::LoadTileMap(const char* fileName)
{
	_doc.LoadFile(fileName);
}

void TileMap::LoadTile(std::string key,int x, int y)
{
	float fX = (float)x;
	float fY = (float)y;
	Tile tempTile(key, fX, fY);
	g_pWorld->addSprite(tempTile);
}

 void TileMap::LoadTileSource()
{
	for (tinyxml2::XMLElement* e = _doc.FirstChildElement("map")->FirstChildElement("tileset")->FirstChildElement("tile"); e != NULL; e = e->NextSiblingElement("tile"))
	{
		// Getting source-Attribute of Image
		std::string tempSource = e->FirstChildElement("image")->Attribute("source");

		// Modify String to be able to parse it into the TextureManager to load the Texture Once!
		std::string word;
		std::stringstream stream(tempSource);
		std::stringstream filePath(tempSource);
		std::stringstream textureSource;

		// Getting the Number of Depth of the Folder-Hierarchy
		int filePathDepth = 0;
		while (getline(filePath, word, '/'))
		{
			if(word != "..")
				filePathDepth++;
		}

		// Modified Folder-Depth for while-Loop
		// "assets/Tiles/Blue tiles/tileBlue_04.png" instead of "assets/Tiles/Blue tiles/tileBlue_04.png/"
		int pathDepth = filePathDepth;
		pathDepth--;

		// Counting StringStream Pieces (word)
		int counter = 0;
		while (getline(stream, word, '/'))
		{
			if (word != "..")
			{
				if (counter < pathDepth)
				{
					textureSource << word << "/";
					counter++;
				}
				else
					textureSource << word;
			}

			if (counter == filePathDepth)
				counter = 0;
		}

		// Parsing StringStream Texture File-Source into string
		std::string source = textureSource.str();

		// Getting Texture-Id from Tiled XML-File
		std::string tileId = e->Attribute("id");
		int id = atoi(tileId.c_str());

		// Insert Map-Pair of TextureId(XML-Tiled-Formatting) and Texture-Key(for the pointer to the Texture of the TextureManager)
		auto inserted = _tileMap.insert(std::make_pair(id, word));

		// Add Texture to TextureManager
		g_pTextureManager->AddTexture(word, source);

		// Count Textures for checking TextureManager
		g_pTextureManager->CountTextures();
	}
}

// just one time as initfunction for populating map
void TileMap::PopulateMap()
{
	tinyxml2::XMLElement* root = _doc.FirstChildElement("map");

	std::string numbOfTilesX = root->Attribute("width");
	std::string numbOfTilesY = root->Attribute("height");

	// String to Integer
	int TilesX  = atoi(numbOfTilesX.c_str());
	int TilesY = atoi(numbOfTilesY.c_str());

	int pixelX = 0;
	int pixelY = 0;

	// Loops through XML and returns ID and File-Path of Texture
	LoadTileSource();

	for (tinyxml2::XMLElement* e = root->FirstChildElement("layer")->FirstChildElement("data")->FirstChildElement("tile"); e != NULL; e = e->NextSiblingElement("tile"))
	{
		// Get tileId as string and cast it to integer
		std::string tileId = e->Attribute("gid");
		int gidId = atoi(tileId.c_str());

		std::string found;

		// search for gidId in _tileMap
		std::map<int, std::string>::iterator i = _tileMap.find(gidId - 1);
		if (i != _tileMap.end())
		{
			found = i->second;
			LoadTile(found, pixelX, pixelY);
		}
		else
			std::cout << _tileMap.size() << std::endl;


		pixelX += _nTileWidth;
		if (pixelX == _nTileWidth * TilesX)
		{
			pixelX = 0;
			pixelY += _nTileHeight;
		}
	}
}

void TileMap::UpdateMap()
{

}

void TileMap::ClearMap()
{
	_tileMap.clear();
}
