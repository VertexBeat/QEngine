#pragma once
#include <map>
#include <memory>
#include <string>
#include "TSingleton.hpp"
#include <SFML\Graphics.hpp>

#define g_pTextureManager TextureManager::Get()

class TextureManager : public TSingleton<TextureManager>
{
public:
	TextureManager();
	~TextureManager();
	// Inits ResourceManager
	bool AddTexture(std::string id,std::string f);
	bool DeleteTexture(std::string id);
	void CountTextures();
	const sf::Texture& GetTexture(std::string id);

private:
	std::map<std::string, std::unique_ptr<sf::Texture>> _textureMap;
	std::map<std::string, std::unique_ptr<sf::Texture>>::iterator _i;

	bool SearchTexture(std::string id);
};

