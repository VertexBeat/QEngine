#include <iostream>
#include "Entity.hpp"
#pragma once
#include "Game.hpp"
int main()
{
	int k;
	// run Game
	g_pGame->run(30);
	std::cin >> k;
	return 0;
}