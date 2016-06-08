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
	sf::RenderWindow window(sf::VideoMode(1920, 1080), "My window");
	g_pTiledLoader->loadLevel("assets/level/testTiles.tmx");
	g_pTiledLoader->setScrollDirection(TiledLoader::SCROLLDIRECTION::x);
	std::multimap<int,Tile> map = g_pTiledLoader->saveAsTileLayer("terrain");
	std::vector<Tile> renderVec;

	int startX = 0;
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