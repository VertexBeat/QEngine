#pragma once
#include <iostream>
#include "Entity.hpp"
#include "Game.hpp"
#include "TiledLoader.hpp"
#include "SFML\Graphics.hpp"
#include "Tile.hpp"
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
	std::multimap<int,Tile> map = g_pTiledLoader->saveAsTileLayer("water");
	// render-vector, we put all of the found map-files into the renderVec for draw-calls later!
	std::vector<Tile> renderVec;

	// map-search-algorithmus for searching specific x/y-values as key and pushing all the tiles in range into !
	int startX = 200;
	int endX = 960;
	for (std::multimap<int,Tile>::iterator it = map.begin(); it != map.end(); it++) {
		if (it->first >= startX && it->first <= endX) {
			renderVec.push_back(it->second);
		}
	}



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
		std::cout << renderVec.size() << std::endl;
		for (int i = 0; i < renderVec.size(); i++) {
			window.draw(renderVec[i].render());
		}

		// end the current frame
		window.display();
	}
}