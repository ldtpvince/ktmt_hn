#pragma once
#include <SFML/Graphics.hpp>
#include <string> // Dung de giu gia tri cua cac button
/*
	Specifies all the functions and data members a Button needs 
*/

//Cac trang thai khac nhau cua button
enum States { IDLE = 0,HOVER, PRESSED };

class Button
{
public:
	Button();
	//Khoi tao button
	Button(sf::Vector2f size, sf::Vector2f position, std::string value ,std::string text, sf::Texture *idleTexture, sf::Texture *hoverTexture
		, sf::Texture *pressedTexture, sf::Color textColor, unsigned int charSize,sf::Font * font);

	//Ham ve cho cac button
	void draw(sf::RenderWindow * window);

	//Cap nhat trang thai cua button dua tren hanh dong cua nguoi dung: Click, hover or Ignore 
	void update(sf::Vector2i mousePos);

	//Cap nhat trang thai duoc chon
	void pressedButton();
	bool isPressedButton();

	//Tra ve gia tri cua button khi nguoi dung chon
	std::string returnValue();

	//Ham gan
	void setText(std::string newText);
	void setTextPos(sf::Vector2f newPos);

	void addText(std::string newText); //adds Text to the Existing text

	//Ham lay 
	std::string getText() const;
private:
	sf::RectangleShape body; //The actual button
	//Gia tri cua button
	sf::Text text;

	//Trang thai cua button va hinh anh hien thi tuong ung
	States buttonState;

	//Gia tri chuoi cua button
	std::string value;

	double counter; //Determines the when the user can select another button

	//Ket cau (texture) cua button
	sf::Texture *idleTexture;
	sf::Texture *hoverTexture;
	sf::Texture *pressedTexture;
};

