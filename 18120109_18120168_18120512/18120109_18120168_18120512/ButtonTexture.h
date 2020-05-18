#pragma once

#include <SFML/Graphics.hpp>

/*
	Dinh nghia 3 ket cau cua moi Button
*/

class ButtonTexture
{
public:
	//Ham khoi tao ket cau cua moi Button
	ButtonTexture(sf::Texture* idleTexture, sf::Texture* hoverTexture, sf::Texture* pressedTexture);

	~ButtonTexture();

	//Ham lay ket cau
	sf::Texture* getIdle() const;
	sf::Texture* getHover() const;
	sf::Texture* getPressed() const;

	//Ham xoa
	void deleteData(); //Huy ket cau 

private:
	sf::Texture* idleTexture;
	sf::Texture* hoverTexture;
	sf::Texture* pressedTexture;
};