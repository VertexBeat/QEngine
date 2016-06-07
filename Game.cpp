#include "Game.hpp"
#include <iostream>
#include "Entity.hpp"
#include "EntityManager.hpp"
#include "BoxObject.hpp"
#include "World.hpp"
#include "Tile.hpp"
#include "TiledManager.hpp"
#include <vector>
#include <SFML/OpenGL.hpp>
#include "Player.hpp"


Game::Game()
	:m_Window(sf::VideoMode(1024, 640), "Arsenal"),
		m_Player(45.f,45.f),
		m_DebugDraw(m_Window) 
{
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;
	g_pWorld->getWorld()->SetDebugDraw(&m_DebugDraw);
	m_DebugDraw.SetFlags(b2Draw::e_shapeBit);
}


Game::~Game()
{
}

void Game::run(int fps)
{
	m_Fps = fps;
	gameLoop();
}

void Game::processEvents()
{
	sf::Event event;
	while (m_Window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			m_Window.close();
		}

		else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::F1)
		{
			if (m_DebugDraw.GetFlags() & b2Draw::e_shapeBit) m_DebugDraw.ClearFlags(b2Draw::e_shapeBit);
			else m_DebugDraw.AppendFlags(b2Draw::e_shapeBit);
		}
		else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::F2)
		{
			if (m_DebugDraw.GetFlags() & b2Draw::e_aabbBit) m_DebugDraw.ClearFlags(b2Draw::e_aabbBit);
			else m_DebugDraw.AppendFlags(b2Draw::e_aabbBit);
		}
		else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::F3)
		{
			if (m_DebugDraw.GetFlags() & b2Draw::e_centerOfMassBit) m_DebugDraw.ClearFlags(b2Draw::e_centerOfMassBit);
			else m_DebugDraw.AppendFlags(b2Draw::e_centerOfMassBit);
		}
	}
}

void Game::update()
{
}

void Game::render()
{
	// clear -> draw -> display !!!
}

void Game::gameLoop()
{
	std::vector<Tile> vTileWorld = g_pTiledManager->loadLevel("level/platformerredone.tmx");

	m_Player.addSpriteSheet("assets/Players/Player Red/redSheet.xml");
	m_Player.AddAnimation("jump", 0, 3);
	m_Player.AddAnimation("walk", 13, 16);
	m_Player.loadState("walk");

	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	sf::Time TimePerFrame = sf::seconds(1.0f / m_Fps);


	while (m_Window.isOpen())
	{

		sf::Time timePerFramePhysiX = sf::seconds(1.f / 60.f);
		sf::Time deltaTime = clock.restart();
		timeSinceLastUpdate += deltaTime;

		processEvents();
		updatePhysiX(deltaTime, timePerFramePhysiX);

		bool jumped = false;

		while (timeSinceLastUpdate >= TimePerFrame) 
		{
			timeSinceLastUpdate -= TimePerFrame;

			sf::Time TimePerFrame = sf::seconds(1.0f / m_Fps);
			
			if (sf::Joystick::isConnected(0)) {
				float axis = sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::PovX);
				m_Player.move(axis / m_Fps);

				if (sf::Joystick::isButtonPressed(0,0)) {
					if (!jumped) {
						m_Player.jump();
						jumped = true;
					}
				}
			}
			// UPDATE
			//update();

			// RENDER
			//render();

			m_Window.clear();
			m_Player.update();

			for (int i = 0; i < vTileWorld.size(); i++) {
				m_Window.draw(vTileWorld[i].render());
			}
			m_Window.draw(m_Player.play());
			g_pWorld->getWorld()->DrawDebugData();
			m_Window.display();
		}
	}
}

void Game::updatePhysiX(const sf::Time & deltaTime, const sf::Time & timePerFrame)
{
	static sf::Time timeSinceLastUpdate = sf::Time::Zero;
	timeSinceLastUpdate += deltaTime;

	g_pWorld->updateGravity(10);

	while (timeSinceLastUpdate > timePerFrame) {
		g_pWorld->updatePhysiX(timePerFrame);
		timeSinceLastUpdate -= timePerFrame;
	}
}
