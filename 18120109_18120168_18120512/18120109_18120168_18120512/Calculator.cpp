#include "Calculator.h"
#include <iostream>


//Khoi tao mac dinh
Calculator::Calculator()
	:window(sf::VideoMode(836, 500), "109 - 168 - 512 Calculator", sf::Style::Close | sf::Style::Titlebar)
{
	//Man hinh
	this->windowTexture.loadFromFile("Sprites/BG Color.png");
	this->windowBody.setSize(sf::Vector2f(836, 500)); // (500, 500)
	this->windowBody.setPosition(sf::Vector2f(0.f, 0.f));
	this->windowBody.setTexture(&windowTexture);

	this->font = new sf::Font(); //Phong chu mat dinh cho tat ca Button
	if (!font->loadFromFile("Fonts/DejaVuSans.ttf"))
	{
		std::cout << "ERROR Opening the FONT " << std::endl;
	}

	//Cai dat cho man hinh cua may tinh
	this->screenTexture.loadFromFile("Sprites/Screen.png");

	//Khoi tao man hinh
	this->screen = Button(sf::Vector2f(836, 150), sf::Vector2f(0, 80), "", "",   // (500, 150)
		&screenTexture, &screenTexture, &screenTexture, sf::Color::Black, 30, this->font);

	this->screen.setTextPos(sf::Vector2f(14, 102));
	this->screen.setNewLineTextPos(0, sf::Vector2f(14, 132));
	this->screen.setNewLineTextPos(1, sf::Vector2f(14, 162));

	this->initNumber(); //Khoi tao cac Button so
	this->initOperators();//Khoi tao cac Button toan tu
	this->initNumeralSystem(); //Khoi tao cac Button he dem

	counter = 0; //Quan ly thoi gian nhap tu ban phim
}

//Huy may tinh
Calculator::~Calculator()
{
	delete this->font;
	for (int i = 0; i < this->numTextures.size(); i++)
	{
		this->numTextures[i].deleteData();
	}

	for (int i = 0; i < this->operTextures.size(); i++)
	{
		this->operTextures[i].deleteData();
	}

	for (int i = 0; i < this->numeralSystems.size(); i++)
	{
		this->numeralTextures[i].deleteData();
	}
}

//Khoi dong may tinh
void Calculator::start()
{
	CalculatorLoop(); //Bat dau vong lap cua may tinh
}

//Vong lap chinh cua may tinh
void Calculator::CalculatorLoop()
{

	while (this->window.isOpen())
	{
		sf::Event evnt;
		//Xu ly cac su kien
		while (window.pollEvent(evnt))
		{
			if (evnt.type == sf::Event::Closed)
			{
				window.close();//Tat may tinh (man hinh)
			}
		}

		//Xoa man hinh
		window.clear();

		//Cap nhat cac thanh phan cua may tinh
		this->updateStuff();

		//Xu ly cac thanh phan cua may tinh
		this->processStuff();

		//Ham ve cac thanh phan cua may tinh
		this->drawStuff();
		//Hien thi cac thanh phan cua may tinh
		window.display();
	}
}

//Ham ve tat ca cac thanh phan cua may tinh
void Calculator::drawStuff()
{
	window.draw(this->windowBody); //Ve nen cua may tinh
								   //Ve cac Button so
	for (int i = 0; i < this->numbers.size(); i++)
	{
		numbers[i].draw(&this->window);
	}

	//Ve cac Button toan tu
	for (int i = 0; i < this->operators.size(); i++)
	{
		operators[i].draw(&this->window);
	}

	//Ve cac Button he dem
	for (int i = 0; i < this->numeralSystems.size(); i++)
	{
		numeralSystems[i].draw(&this->window);
	}

	//Ve man hinh cua may tinh
	this->screen.draw(&this->window);
}

//Cap nhat cac thanh phan cua may tinh 
void Calculator::updateStuff()
{
	//Cap nhat trang thai cua Button so
	for (int i = 0; i < this->numbers.size(); i++)
	{
		numbers[i].update(sf::Mouse::getPosition(this->window));
	}

	//Cap nhat trang thai cua Button toan tu
	for (int i = 0; i < this->operators.size(); i++)
	{
		operators[i].update(sf::Mouse::getPosition(this->window));
	}

	//Cap nhat trang thai cua Button he dem
	for (int i = 0; i < this->numeralSystems.size(); i++)
	{
		numeralSystems[i].update(sf::Mouse::getPosition(this->window));
		if (numeralSystems[i].isPressedButton())
		{
			if (i == 0)
			{
				if (screen.getText() != ""&& is_number(screen.getText()) && MODE != 10)
				{
					this->screen.setText(this->checker.changeNumeral(this->screen.getText(), MODE, 10));
				}
				MODE = 10;
			}
			else if (i == 1)
			{
				if (screen.getText() != ""&& is_number(screen.getText()) && MODE != 2)
				{
					this->screen.setText(this->checker.changeNumeral(this->screen.getText(), MODE, 2));
				}
				MODE = 2;
			}
			else
			{
				if (screen.getText() != ""&& is_number(screen.getText()) && MODE != 16)
				{
					this->screen.setText(this->checker.changeNumeral(this->screen.getText(), MODE, 16));
				}
				MODE = 16;
			}
		}
	}

	//Hien thi Button he dem duoc chon
	if (MODE == 2) //He nhi phan
	{
		numeralSystems[1].pressedButton();
	}
	else if (MODE == 10) //He thap phan
	{
		numeralSystems[0].pressedButton();
	}
	else //He thap luc phan
	{
		numeralSystems[2].pressedButton();
	}
	//Cap nhat man hinh may tinh
	this->screen.update(sf::Mouse::getPosition(this->window));
}

//Ham xu ly cac thanh phan cua may tinh
void Calculator::processStuff()
{
	std::string pressedStuff = "";

	//Khi nguoi dung chon Button so
	for (int i = 0; i < this->numbers.size(); i++)
	{
		pressedStuff += this->numbers[i].returnValue();
	}

	//Khi nguoi dung chon Button toan tu
	for (int i = 0; i < this->operators.size(); i++)
	{
		pressedStuff += this->operators[i].returnValue();
	}

	//Khi nguoi dung chon Button he dem
	for (int i = 0; i < numeralSystems.size(); i++)
	{
		pressedStuff += this->numeralSystems[i].returnValue();
	}

	//Khi nguoi dung nhap tu ban phim
	pressedStuff += this->keyboardInput();

	if (pressedStuff != "")
	{
		this->screenProcessor(pressedStuff); //Van ban tren man hinh may tinh
	}
}

//Khoi tao cac Button so
void Calculator::initNumber()
{
	//Kich thuoc Button so
	sf::Vector2f numSize(112, 58);

	std::string numsValue[] = { "0", "1", "2", "3", "A", "D", "4", "5", "6", "B", "E", "7", "8", "9", "C", "F" };

	int total = sizeof(numsValue) / sizeof(std::string);

	//Khoi tao ket cau so tu 0 - 9
	for (int i = 0; i < total; i++)
	{
		sf::Texture* tempIdle = new sf::Texture();
		sf::Texture* tempHover = new sf::Texture();
		sf::Texture* tempPressed = new sf::Texture();
		tempIdle->loadFromFile("Sprites/#" + numsValue[i] + ".png");
		tempHover->loadFromFile("Sprites/#" + numsValue[i] + " H.png");
		tempPressed->loadFromFile("Sprites/#" + numsValue[i] + " H.png");
		numTextures.push_back(ButtonTexture(tempIdle, tempHover, tempPressed));
	}

	//Khoi tao so 0 rieng boi vi vi tri dat dac biet
	this->numbers.push_back(Button(
		numSize, sf::Vector2f(20, 427), "0", "",
		numTextures[0].getIdle(), numTextures[0].getHover(), numTextures[0].getPressed(),
		sf::Color::Black, 30, this->font));

	float xPos = 139; //Quan ly vi tri XPos cua Button
	float yPos = 427; //Quan ly vi tri YPos cua Button

					  //Khoi tao cac Button so tu 1-9 va A-F
	for (int i = 1; i < total; i++)
	{
		this->numbers.push_back(Button(
			numSize, sf::Vector2f(xPos, yPos), numsValue[i], "",
			numTextures[i].getIdle(), numTextures[i].getHover(), numTextures[i].getPressed(),
			sf::Color::Black, 30, this->font));

		if (i == 5)
		{
			//Cai lai vi tri bat dau
			xPos = 139;
			yPos = 366;
		}
		else if (i == 10)
		{
			//Cai lai vi tri bat dau
			xPos = 139;
			yPos = 305;
		}
		else
		{
			xPos += 115;
		}
	}

}

//Khoi tao cac Button toan tu
void Calculator::initOperators()
{

	sf::Vector2f operSize(58, 58);

	//Cac toan tu: Bo sung << là "(", >> là ")", &, | là "@", ^, ~
	std::string operValues[] = { "=", "+", "-", "x", "Div", ".", "(", ")", "&", "@", "^", "~", "Del", "AC" };
	std::string operValuesText[] = { "=", "+", "-","*", "/", ".", "<<", ">>", "&", "|", "^", "~" };

	int operAmount = sizeof(operValues) / sizeof(std::string);

	//Khoi tao ket cau cho cac toan tu
	for (int i = 0; i < operAmount; i++)
	{
		sf::Texture* tempIdle = new sf::Texture();
		sf::Texture* tempHover = new sf::Texture();
		sf::Texture* tempPressed = new sf::Texture();

		tempIdle->loadFromFile("Sprites/" + operValues[i] + ".png");
		tempHover->loadFromFile("Sprites/" + operValues[i] + " H.png");
		tempPressed->loadFromFile("Sprites/" + operValues[i] + " H.png");

		operTextures.push_back(ButtonTexture(tempIdle, tempHover, tempPressed));
	}

	//Khoi tao cac toan tu
	//Cac toan tu =, +, -, *, Div, ., <<, >> cung nhau

	int xPos = 49;  // = xPosition
	int yPos = 244; // = yPosition

	for (int i = 0; i < 12; i++)
	{
		//if (i == 4) //Cai dat toan tu Div
		//{
		//	operators.push_back(Button(operSize, sf::Vector2f(xPos, yPos), "/", "",
		//		operTextures[i].getIdle(), operTextures[i].getHover(), operTextures[i].getPressed(),
		//		sf::Color::Black, 30, this->font));
		//}
		//else
		{
			operators.push_back(Button(operSize, sf::Vector2f(xPos, yPos), operValuesText[i], "",
				operTextures[i].getIdle(), operTextures[i].getHover(), operTextures[i].getPressed(),
				sf::Color::Black, 30, this->font));
		}

		xPos += 65; //Di chuyen XPos sang phai 72 don vi voi moi Button
	}

	//Cac toan tu : AC, Del
	xPos = 49; //Del XPosition
	yPos = 305;//Del YPosition

	for (int i = 12; i < operAmount; i++)
	{
		operators.push_back(Button(operSize, sf::Vector2f(xPos, yPos), operValues[i], "",
			operTextures[i].getIdle(), operTextures[i].getHover(), operTextures[i].getPressed(),
			sf::Color::Black, 30, this->font));
		yPos += 61;
	}

}

//Khoi tao he dem
void Calculator::initNumeralSystem()
{
	sf::Vector2f numeralSize(112, 58);

	//Cac he dem: DEC, BIN, HEX
	std::string numeralValues[] = { "d", "b", "h" };

	int numeralAmount = sizeof(numeralValues) / sizeof(std::string);

	//Khoi tao ket cau cho cac he dem
	for (int i = 0; i < numeralAmount; i++)
	{
		sf::Texture* tempIdle = new sf::Texture();
		sf::Texture* tempHover = new sf::Texture();
		sf::Texture* tempPressed = new sf::Texture();

		tempIdle->loadFromFile("Sprites/" + numeralValues[i] + ".png");
		tempHover->loadFromFile("Sprites/" + numeralValues[i] + " H.png");
		tempPressed->loadFromFile("Sprites/" + numeralValues[i] + " H.png");

		numeralTextures.push_back(ButtonTexture(tempIdle, tempHover, tempPressed));
	}

	//Cac he dem

	float xPos = 716; //Quan ly vi tri XPos cua Button
	float yPos = 427; //Quan ly vi tri YPos cua Button

					  //Khoi tao cac Button he dem
	for (int i = 0; i < numeralAmount; i++)
	{
		this->numeralSystems.push_back(Button(
			numeralSize, sf::Vector2f(xPos, yPos), "", "",
			numeralTextures[i].getIdle(), numeralTextures[i].getHover(), numeralTextures[i].getPressed(),
			sf::Color::Black, 30, this->font));

		yPos -= 61;
	}
}

//Xu ly van ban tren man hinh de cap nhat
void Calculator::screenProcessor(std::string toAdd)
{
	//Kiem tra neu Button Backspace (Del) hoac AC duoc chon
	//Va Button toan tu = duoc chon

	//Button Backspace (Del) duoc chon va noi dung man hinh khac rong
	if (toAdd == "Del")
	{
		if (screen.getText() != "")
		{
			//Xoa phan tu cuoi cung trong van ban
			this->screen.setText(this->screen.getText().erase(this->screen.getText().length() - 1));
		}
	}
	else if (toAdd == "AC")
	{
		//Xoa toan bo man hinh
		this->screen.setText("", true);
	}
	else if (toAdd == "=")
	{
		//Lop Math kiem tra tinh hop le cua bieu thuc
		//Neu khong hop le se xuat ra ERROR

		//Kiem tra va tinh toan sau do xuat ra man hinh
		if (this->screen.getText().length() > 0)
		{
			this->screen.setText(this->checker.doMath(this->screen.getText(), MODE));
		}

	}
	else
	{
		//Them vao noi dung man hinh neu it hon 43 ki tu
		/*if (this->screen.getText().length() < 43)
		{
			if (this->screen.getText() != "ERROR")
			{
				this->screen.addText(toAdd);
			}
		}*/
		this->screen.addText(toAdd);
	}
}

//Cho phep nguoi dung nhap tu ban phim
std::string Calculator::keyboardInput()
{
	double timer = 8.5; //Su dung de quan ly so luong duoc nhap vao tai 1 khoang thoi gian
	std::string answer = "";

	if (counter >= timer)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num0))
		{
			answer = "0";
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
		{
			answer = "1";
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))
		{
			answer = "2";
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3))
		{
			answer = "3";
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num4))
		{
			answer = "4";
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num5))
		{
			answer = "5";
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num6))
		{
			answer = "6";
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num7))
		{
			answer = "7";
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num8))
		{
			answer = "8";
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num9))
		{
			answer = "9";
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			answer = "A";
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::B))
		{
			answer = "B";
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::C))
		{
			answer = "C";
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			answer = "D";
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
		{
			answer = "E";
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::F))
		{
			answer = "F";
		}
		if ((sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) ||
			sf::Keyboard::isKeyPressed(sf::Keyboard::RShift)) &&
			sf::Keyboard::isKeyPressed(sf::Keyboard::Dash))
		{
			answer = "-";
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace))
		{
			answer = "Del";
		}
		if ((sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) ||
			sf::Keyboard::isKeyPressed(sf::Keyboard::RShift)) &&
			sf::Keyboard::isKeyPressed(sf::Keyboard::Num8))
		{
			answer = "x";
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Slash))
		{
			answer = "/";
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Period))
		{
			answer = ".";
		}
		if ((sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) ||
			sf::Keyboard::isKeyPressed(sf::Keyboard::RShift)) &&
			sf::Keyboard::isKeyPressed(sf::Keyboard::Num9))
		{
			answer = "(";
		}
		if ((sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) ||
			sf::Keyboard::isKeyPressed(sf::Keyboard::RShift)) &&
			sf::Keyboard::isKeyPressed(sf::Keyboard::Num0))
		{
			answer = ")";
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Equal))
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
			{
				answer = "+";
			}
			else
			{
				std::cout << "=" << std::endl;
				answer = "=";
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
		{
			std::cout << "Enter" << std::endl;
			answer = "=";
		}

		counter = 0; //Gan lai counter
	}
	counter += 0.03;
	return answer;
}

bool is_number(const std::string& s)
{
	for (int i = 0; i < s.length(); i++)
		if (!((s[i] >= '0'&&s[i] <= '9') || (s[i] >= 'A'&&s[i] <= 'F')))
			return false;
	return true;
}