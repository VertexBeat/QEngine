#pragma once
#include "SFMLDebugDraw.hpp"
#include "TSingleton.hpp"
#include "Player.hpp"

#define g_pGame Game::Get()
class Game : public TSingleton<Game>
{
public:
	Game();
	~Game();
	void run(int fps);
private:
	void processEvents();
	void update();
	void render();
	void gameLoop();
	void updatePhysiX(const sf::Time& deltaTime, const sf::Time& timePerFrame);

	sf::RenderWindow m_Window;
	sf::ContextSettings m_Settings;
	SFMLDebugDraw m_DebugDraw;

	// player of game
	Player m_Player;

	int m_Fps;
};

