#pragma once
#include "tinyxml2.h"
#include <string>
#include <map>

enum Orientation{orthogonal,isometric,staggered};
enum RenderOrder{rightdown,rightup,leftdown,leftup};
enum Format{png,gif,jpg,bmp};
enum Layer{background,layer1,layer2,layer3,layer4,layer5,layer6};

class TileMap
{
public:
	TileMap();
	TileMap(int nTileHeight, int nTileWidth, Orientation orientation, RenderOrder renderOrder, Format format, Layer layer);
	~TileMap();
	// Initiates LevelFile
	void Init(const char* fileName);
	void PopulateMap();
	void UpdateMap();
	void ClearMap();
	std::map<int, std::string> GetMap() { return _tileMap; };
private:
	// Loads LevelFile
	void LoadTileMap(const char* fileName);
	void LoadTile(std::string key, int x, int y);
	void LoadTileSource();

	bool CheckOrientation(Orientation orientation);
	bool CheckRenderOrder(RenderOrder renderOrder);
	bool CheckTileSize(int tileWidth, int tileHeight);
	//bool CheckFormat(Format format);

private:
	tinyxml2::XMLDocument _doc;
	int _nTileHeight;
	int _nTileWidth;

	std::map<int, std::string> _tileMap;

	Orientation _orientation;
	RenderOrder _renderOrder;
	Format _format;
	Layer _layer;
};

