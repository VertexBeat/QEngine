#include "TiledManager.hpp"
#include "tinyxml2.h"
#include <iostream>
#include "TextureManager.hpp"
#include "Tile.hpp"
#include <vector>
#include <map>

TiledManager::TiledManager()
{
	m_TileVec.clear();
}


TiledManager::~TiledManager()
{
}

std::vector<Tile> TiledManager::loadLevel(const char* fileName)
{
	if (!m_Doc.LoadFile(fileName))
	{
		printf("load file=[%s] succeeded\n", fileName);
	}
	else
	{
		printf("load file=[%s] failed\n", fileName);
	}

	for (tinyxml2::XMLElement* e = m_Doc.FirstChildElement()->FirstChildElement("tileset")->FirstChildElement("tile"); e != NULL; e = e->NextSiblingElement("tile"))
	{

		// get tile id for textureManagement
		const char* tagId = nullptr;
		tagId = e->Attribute("id");
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


	}

	std::string objName;
	for (tinyxml2::XMLElement* e = m_Doc.FirstChildElement()->FirstChildElement("objectgroup"); e != NULL; e = e->NextSiblingElement("objectgroup"))
	{
		const char* objectGroupName = nullptr;
		objectGroupName = e->Attribute("name");
		objName = objectGroupName;
		std::cout << "---------------------------------------------------------------" << std::endl;
		std::cout << objName << std::endl;

		for (tinyxml2::XMLElement* f = e->FirstChildElement("object"); f != NULL; f = f->NextSiblingElement("object"))
		{
			std::cout << "New Object!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << std::endl;
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

			//add texture to textureManager with id of textureTag and set texture on tile

			// used for finding the right texture in m_TextureIdentificationMap for getting the TextureTag
			int nTextureFinder = --tmpGid;

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
			}

			// initialize box2d framework
			if (objName == "tiles") {
				Tile tmpTile(fPosX, fPosY, fWidth, fHeight, true);
				tmpTile.loadTexture(resultTag, resultPath);
				tmpTile.setType(BODYTYPE::staticBody);
				tmpTile.InitBox2d();
				m_TileVec.push_back(tmpTile);
				std::cout << "Collision detected" << std::endl;
			}
			else {
				Tile tmpTile(fPosX, fPosY, fWidth, fHeight, false);
				tmpTile.loadTexture(resultTag, resultPath);
				m_TileVec.push_back(tmpTile);
				std::cout << "Collision not detected" << std::endl;
			}
		}
	}
	
	std::cout << "------------------SIZE---------------------------" << std::endl;
	std::cout << m_TileVec.size() << std::endl;
	return m_TileVec;
}
