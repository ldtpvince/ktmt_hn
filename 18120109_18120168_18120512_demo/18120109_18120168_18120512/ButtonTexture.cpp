#include "ButtonTexture.h"
#include <iostream>

//Ham khoi tao ket cau cua moi Button
ButtonTexture::ButtonTexture(sf::Texture* idleTexture, sf::Texture* hoverTexture, sf::Texture* pressedTexture)
{
	this->idleTexture = idleTexture;
	this->hoverTexture = hoverTexture;
	this->pressedTexture = pressedTexture;
}

ButtonTexture::~ButtonTexture()
{

}


sf::Texture* ButtonTexture::getIdle() const
{
	return idleTexture;
}

sf::Texture* ButtonTexture::getHover() const
{
	return hoverTexture;
}

sf::Texture* ButtonTexture::getPressed() const
{
	return pressedTexture;
}

void ButtonTexture::deleteData()
{
	delete idleTexture;
	delete hoverTexture;
	delete pressedTexture;
}

