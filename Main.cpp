#pragma once
#include <iostream>
#include "Entity.hpp"
#include "Game.hpp"
#include "TiledLoader.hpp"
#include "SFML\Graphics.hpp"
#include "Tile.hpp"
#include "Scene.hpp"
#include "World.hpp"
void TestGameLoop();

int main()
{
	int k;
	// run Game
	//g_pGame->run(30);
	TestGameLoop();
	std::cin >> k;
	return 0;
}

void TestGameLoop() {
	sf::RenderWindow window(sf::VideoMode(1920, 1080), "QEngine");
	// load level testTiles.tmx and apply scaling on tiles, so they fit in the window!
	g_pTiledLoader->loadLevel("assets/level/testTiles.tmx",0.84375);
	// set the scrolldirection -> how the game is going to be scrolled -> we are mapping the values of x/y depending on that!
	g_pTiledLoader->setScrollDirection(TiledLoader::SCROLLDIRECTION::x);
	// get TileLayer and put them into a mulimap, so we have access to every tile over his x/y position!
	std::multimap<int, Tile> terrain_map = g_pTiledLoader->saveAsTileLayer("terrain");
	std::multimap<int,Tile> water_map = g_pTiledLoader->saveAsTileLayer("water");

	Scene scene;
	scene.addTileLayerToScene(terrain_map);
	scene.addTileLayerToScene(water_map);
	std::vector<sf::Sprite> renderVec = scene.renderSceneTiles(0, 1080);

	// run the program as long as the window is open
	while (window.isOpen())
	{
		// check all the window's events that were triggered since the last iteration of the loop
		sf::Event event;
		while (window.pollEvent(event))
		{
			// "close requested" event: we close the window
			if (event.type == sf::Event::Closed)
				window.close();
		}

		// clear the window with black color
		window.clear();

		// draw everything here...
		
		for (int i = 0; i < renderVec.size(); i++) {
			window.draw(renderVec[i]);
		}

		// end the current frame
		window.display();
	}
}