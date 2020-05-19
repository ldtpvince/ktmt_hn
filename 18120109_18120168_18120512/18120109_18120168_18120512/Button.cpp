#include "Button.h"
#include <iostream>


Button::Button()
{
}

//Khoi tao Button
Button::Button(sf::Vector2f size, sf::Vector2f position, std::string value , std::string text,
	sf::Texture *idleTexture, sf::Texture *hoverTexture, sf::Texture *pressedTexture, sf::Color textColor, unsigned int charSize
	, sf::Font * font)
{
	//Cai dat cho Button: Kich thuoc, vi tri va ket cau
	this->body.setSize(size);
	this->body.setPosition(position);
	this->body.setTexture(idleTexture);

	//Luu gia tri chuoi cua button
	this->value = value;

	//Gan van ban cho Button: Van ban (text), co chu, mau va Font
	this->text.setString(text);				//Gan text cho button
	this->text.setCharacterSize(charSize);  //Co chu
	this->text.setFillColor(textColor); 
	this->text.setFont(*font);

	// Cai dat van ban o dong moi
	for (int i = 0; i < 2; i++) {
		this->newText[i].setString("");
		this->newText[i].setCharacterSize(charSize);
		this->newText[i].setFillColor(textColor);
		this->newText[i].setFont(*font);
	}

	//Cai dat vi tri cua Button
	/*this->text.setPosition(sf::Vector2f(
		position.x + (this->body.getGlobalBounds().width / 2.f) - (this->text.getGlobalBounds().width /2)
		, position.y + (this->body.getGlobalBounds().height / 2.f) - (this->text.getGlobalBounds().height ) 
		+ (this->text.getGlobalBounds().height / 7.f)));*/

	//Cai dat ket cau cho Button
	this->idleTexture = idleTexture;
	this->hoverTexture = hoverTexture;
	this->pressedTexture = pressedTexture;

	//Khoi tao trang thai dau tien cua Button la IDLE
	this->buttonState = IDLE; 

	counter = 0; //Khoi tao bang 0
}

//Ham ve button
void Button::draw(sf::RenderWindow * window)
{
	window->draw(this->body); //Ve button tren window 
	window->draw(this->text); //Ve van ban Button len Window
	window->draw(this->newText[0]);
	window->draw(this->newText[1]);
}

//Cap nhat trang thai Button dua tren thao tac cua nguoi dung: Click, Hover or Ignore 
void Button::update(sf::Vector2i mousePos)
{
	this->buttonState = IDLE; //Khong co gi xay ra: gan Button la IDLE

	//Vi tri con chuot nam tren Button: HOVER
	if (this->body.getGlobalBounds().contains(sf::Vector2f(mousePos.x, mousePos.y)))
	{
		this->buttonState = HOVER;
		
		//Khi nguoi dung chon Button
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			this->buttonState = PRESSED;
		}
	}

	//Thay doi ket cau Button dua tren trang thai cua no
	switch (this->buttonState)
	{
	case IDLE:
		this->body.setTexture(idleTexture);
		break;

	case HOVER:
		this->body.setTexture(hoverTexture);
		break;
	case PRESSED:
		this->body.setTexture(pressedTexture); 
		break;

	default:
		this->body.setFillColor(sf::Color::Red);
		break;
	}
}

void Button::pressedButton()
{
	this->buttonState = PRESSED;
	this->body.setTexture(pressedTexture);
}

bool Button::isPressedButton()
{
	return (buttonState == PRESSED);
}

//Tra ve gia tri cua Button khi nguoi dung chon Button
std::string Button::returnValue()
{
	std::string tempValue = ""; //Gia tri tra ve neu nguoi dung khong nhan Button
	//Neu nguoi dung nhan Button thi kiem tra thoi gian

	if (this->buttonState == PRESSED)
	{

		if (counter >= 8.5)
		{
			counter = 0; //Khoi dong lai may thoi gian
			//std::cout << "Button Returns: " << value << std::endl;
			tempValue = value;
		}
	}
	counter += 0.03;

	return tempValue; //Tra ve gia tri
}


//Ham gan
void Button::setText(std::string newText, bool setAll)
{
	if (newText.length() <= 43) {
		this->text.setString(newText);
		this->newText[0].setString("");
		this->newText[1].setString("");
	}
	else if (newText.length() <= 86) {
		this->text.setString(newText.substr(0, 43));
		this->newText[0].setString(newText.substr(43));
		this->newText[1].setString("");
	}
	else {
		this->text.setString(newText.substr(0, 43));
		this->newText[0].setString(newText.substr(43, 43));
		this->newText[1].setString(newText.substr(86));
	}

	if (setAll) {
		this->text.setString(newText);
		this->newText[0].setString(newText);
		this->newText[1].setString(newText);
	}
}

void Button::setTextPos(sf::Vector2f newPos)
{
	this->text.setPosition(newPos);
}

sf::Vector2f Button::getTextPos() {
	return this->text.getPosition();
}

void Button::setNewLineTextPos(int line, sf::Vector2f newPos)
{
	this->newText[line].setPosition(newPos);
}

//Them van ban vao mot van ban ton tai
void Button::addText(std::string newText)
{
	if (this->text.getString().getSize() < 43) {
		this->text.setString(this->text.getString() + newText);
		std::cout << this->text.getString().getSize();
	}
	else if (this->newText[0].getString().getSize() < 43) {
		this->newText[0].setString(this->newText[0].getString() + newText);
	}
	else {
		this->newText[1].setString(this->newText[1].getString() + newText);
	}
}

//Ham lay
std::string Button::getText() const
{
	return this->text.getString() + this->newText[0].getString() + this->newText[1].getString();
}