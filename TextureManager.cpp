#include "TextureManager.hpp"
#include <map>
#include <memory>
#include <string>
#include <iostream>
#include <assert.h>
#include <SFML\Graphics.hpp>



TextureManager::TextureManager()
{
}


TextureManager::~TextureManager()
{
}

bool TextureManager::AddTexture(std::string id,std::string f)
{
	std::unique_ptr<sf::Texture> texture(new sf::Texture());
	if (!texture->loadFromFile(f))
	{
		std::cout << "File: " << f << " couldn`t be loaded!" << std::endl;
	}

	if (SearchTexture(id))
	{
		//std::cout << "Texture: " << id << " was already added to textureMap!" << std::endl;
	}
	else 
	{
		auto inserted = _textureMap.insert(std::make_pair(id, std::move(texture)));
		std::cout << "|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||" << std::endl;
		std::cout << "Texture: " << id << " added to textureMap!" << std::endl;
		assert(inserted.second);
	}

	return true;
}

bool TextureManager::DeleteTexture(std::string id)
{
	_i = _textureMap.find(id);
	if (_i != _textureMap.end())
	{
		_textureMap.erase(_i);
		//std::cout << "Texture with ID: " << id << " has been erased" << std::endl;
		return true;
	}
	//std::cout << "Texture with ID: " << id << " has not been found in Map!" << std::endl;
	return false;
}

void TextureManager::CountTextures()
{
	std::cout << "We count " << _textureMap.size() << " Textures" << std::endl;
}

const sf::Texture& TextureManager::GetTexture(std::string id)
{
	auto found = _textureMap.find(id);
	assert(found != _textureMap.end());
	
	return *found->second;
}

bool TextureManager::SearchTexture(std::string id)
{
	_i = _textureMap.find(id);
	if (_i != _textureMap.end())
	{
		//std::cout << "Texture with ID: " << id << " is existing in textureMap!" << std::endl;
		return true;
	}
	//std::cout << "Texture with ID: " << id << " is not existing in textureMap!" << std::endl;
	return false;
}
