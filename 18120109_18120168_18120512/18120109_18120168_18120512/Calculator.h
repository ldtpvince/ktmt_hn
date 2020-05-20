#pragma once
#include <SFML/Graphics.hpp>
#include "Button.h"
#include <vector>
#include "ButtonTexture.h"
#include "Math.h"

class Calculator
{
public:

	Calculator();//Khoi tao mat dinh
	void start(); //Kich hoat may tinh 
	~Calculator();//Huy may tinh
private:
	void CalculatorLoop();//Vong  lap cua mat tinh
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

	int MODE = 10; //He co so 10 ban dau

				   //Quan ly thoi gian nhap tu ban phim
	double counter;

	//Thuc hien tinh toan cua may tinh 
	Math checker;

	//Bien giu che do: So nguyen lon hay so cham dong
	bool TYPE = true; // Mac dinh la so nguyen lon
};

//Ham kiem tra chuoi khong chua toan tu de chuyen he dem
bool is_number(const std::string& s, int mode);