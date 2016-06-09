#include "Player.hpp"
#include <iostream>
#include "TextureManager.hpp"

#define BOX2D_CONVERTER 128.f;

Player::Player(int controllerId)
{
	// needs overwork
	m_Position.x = 500.f;
	m_Position.y = 100.f;
	m_ControllerId = controllerId;
	m_Type = BODYTYPE::dynamicBody;
	InitBox2d();
}

Player::Player(float x, float y)
{
	m_Position.x = 50.f;
	m_Position.y = 70.f;
	m_Type = BODYTYPE::dynamicBody;
	setAsBox(x, y);
	InitBox2d();
}

Player::Player()
{
	m_Position.x = 0.f;
	m_Position.y = 0.f;
	m_Type = BODYTYPE::dynamicBody;
	setAsBox(m_Position.x, m_Position.y);
	InitBox2d();
}


Player::~Player()
{
}

void Player::move(float movement)
{
	// move sprite
	m_Position.x += movement;
}

void Player::jump()
{
	//to change velocity by 10
	float impulse = m_Box2d.getBody()->GetMass();
	m_Box2d.getBody()->ApplyLinearImpulse(b2Vec2(0, -impulse), m_Box2d.getBody()->GetWorldCenter(),true);
	std::cout << "Mass" << m_Box2d.getBody()->GetMass() << std::endl;
}

void Player::update()
{
	updateBox2d();
	//m_Position.y = m_Box2d.getPosition().y;
	float x = m_Position.x / BOX2D_CONVERTER;
	float y = m_Position.y / BOX2D_CONVERTER;
	b2Vec2 b2Pos = b2Vec2(x,y);
	m_Box2d.setPosition(b2Pos);
}

void Player::AddAnimation(std::string state, int nStart, int nFrames)
{
	Animation anim;
	std::vector<sf::Sprite> animSprites;
	for (int i = nStart; i < nFrames; i++) 
	{
		animSprites.push_back(m_SpriteVec[i]);
	}

	anim.getSprites(animSprites);
	m_AnimationMap.insert(std::make_pair(state, anim));
}

// frameCounter
void Player::loadState(std::string state)
{
	sf::Sprite sprite;
	std::map<std::string, Animation>::iterator i = m_AnimationMap.find(state);
	if (i != m_AnimationMap.end()) {
		m_LoadedAnimation = i->second;
	}
}

sf::Sprite Player::play()
{
	sf::Sprite sprite;
	sprite = m_LoadedAnimation.playAnimation();
	sprite.setPosition(m_Position);
	return sprite;
}

void Player::setAsBox(float x, float y)
{
	m_BoxDimension.x = x;
	m_BoxDimension.y = y;
}

// add spritesheet to texture-manager
// load texture into _sprite
void Player::addSpriteSheet(const char* filePathConfig)
{
	// load Configurationfile

	if (!m_Doc.LoadFile(filePathConfig))
	{
		printf("load file=[%s] succeeded\n", filePathConfig);
	}
	else
	{
		printf("load file=[%s] failed\n", filePathConfig);
	}
	// --------------------------

	const char* cPath = m_Doc.FirstChildElement("TextureAtlas")->Attribute("imagePath");
	std::string sSheetPath = cPath;
	std::string imagePathFile = cPath;
	
	// get spriteSheetName for textureManager identification
	std::string delimiter = "/";
	size_t pos = 0;
	std::string token;
	while ((pos = sSheetPath.find(delimiter)) != std::string::npos) {
		token = sSheetPath.substr(0, pos);
		sSheetPath.erase(0, pos + delimiter.length());
	}
	std::string sSpriteSheetName = sSheetPath;
	// -------------------------------

	// save texture in texturemanager and save in member-file
	g_pTextureManager->AddTexture(sSpriteSheetName, imagePathFile);
	std::cout << "Name: " << sSheetPath << std::endl;
	// -------------------------------

	for (tinyxml2::XMLElement* e = m_Doc.FirstChildElement("TextureAtlas")->FirstChildElement("sprite"); e != NULL; e = e->NextSiblingElement("sprite")) 
	{
		const char* name;
		name = e->Attribute("n");

		const char* cXPos;
		cXPos = e->Attribute("x");

		const char* cYPos;
		cYPos = e->Attribute("y");

		const char* cWidth;
		cWidth = e->Attribute("w");

		const char* cHeight;
		cHeight = e->Attribute("h");

		const char* cPivotX;
		cPivotX = e->Attribute("pX");

		const char* cPivotY;
		cPivotY = e->Attribute("pY");

		const char* cRotation;
		cRotation = e->Attribute("r");

		std::cout << "Name:" << name << std::endl;

		sf::IntRect rect(atoi(cXPos), atoi(cYPos), atoi(cWidth), atoi(cHeight));
		const sf::Texture& texture = g_pTextureManager->GetTexture(sSpriteSheetName);
		sf::Sprite sprite(texture, rect);
		sprite.setOrigin(atof(cWidth) * atof(cPivotX), atof(cHeight) * atof(cPivotY));
		if ((cRotation != NULL) && (cRotation[0] == '\0')) {
			//nothing
		}
		else {
			sprite.setRotation(-90.f);
		}
		m_SpriteVec.push_back(sprite);
		std::cout << m_SpriteVec.size() << std::endl;
		std::cout << "Width: " << atof(cWidth) << " Height: " << atof(cHeight) << " X: " << atoi(cXPos) << " Y: " << atoi(cYPos) << std::endl;
	}
}

// if m_Collision is true init Box2D!
void Player::InitBox2d()
{
	float boxPositionX = m_Position.x / BOX2D_CONVERTER;
	float boxPositionY = m_Position.y / BOX2D_CONVERTER;
	float boxWidth = m_BoxDimension.x / BOX2D_CONVERTER;
	float boxHeight = m_BoxDimension.y / BOX2D_CONVERTER;
	m_Box2d = BoxObject(boxPositionX, boxPositionY, boxWidth, boxHeight, m_Type);

}
//----------------------------------

// get updated Box2d coordinates and rotation 
// convert them into coordinates to display sprites properly
void Player::updateBox2d()
{
	m_Box2d.update();
	m_Position.y = m_Box2d.getPosition().y * BOX2D_CONVERTER;
	//m_Position.x = m_Box2d.getPosition().x * BOX2D_CONVERTER;
	m_BoxDimension.x = m_Box2d.getDimension().x * BOX2D_CONVERTER;
	m_BoxDimension.y = m_Box2d.getDimension().y * BOX2D_CONVERTER;
	m_Angle = m_Box2d.getAngle();
}
//----------------------------------
