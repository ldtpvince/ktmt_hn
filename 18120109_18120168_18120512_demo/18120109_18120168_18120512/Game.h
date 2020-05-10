#pragma once
#include <SFML/Graphics.hpp>
#include "Button.h"
#include <vector>
#include "ButtonTexture.h"
#include "Math.h"

class Game
{
public:
	
	Game();//Khoi tao mat dinh
	void start(); //Kich hoat may tinh 
	~Game();//Huy may tinh
private:
	void gameLoop();//Vong  lap cua mat tinh
	void drawStuff(); //Ham ve cac thanh phan co trong may tinh
	void updateStuff(); //Ham cap nhat cac thanh phan cua may tinh
	void processStuff(); //Ham xu ly cac thanh phan cua may tinh
	void initNumber(); //Khoi tao cac Button so
	void initOperators(); //Khoi tao cac Button toan tu  
	void initNumeralSystem(); //Khoi tao he dem
	void screenProcessor(std::string toAdd); //Xu ly van ban tren may tinh de cap nhat
	std::string keyboardInput();//Cho phep nhap bang ban phim
private:
	sf::RenderWindow window;//Man hinh may tinh
	sf::Texture windowTexture; 
	sf::RectangleShape windowBody;

	sf::Font *font; //Font chu

	//Ket cau man hinh
	sf::Texture screenTexture;
	
	//Man hinh thuc su
	Button screen; 

	//Ket cau cua so
	std::vector<ButtonTexture> numTextures;

	//Tat ca Button cua so
	std::vector<Button> numbers; 

	//Ket cau cua toan tu
	std::vector<ButtonTexture> operTextures;

	//Tat ca Button cua toan tu
	std::vector<Button> operators;

	//He dem
	std::vector <Button> numeralSystems;

	// Ket cau cua Button he dem
	std::vector <ButtonTexture> numeralTextures;

	//Quan ly thoi gian nhap tu ban phim
	double counter;

	//Thuc hien tinh toan cua may tinh 
	Math checker;
};

