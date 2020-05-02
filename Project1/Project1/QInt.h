#pragma once
#include <iostream>
#include <string>
#include <istream>
#include <ostream>

class QInt {
private:
	int data[4];
	int binLen;

public:
	QInt();

	std::string QIntToBin();
	string QIntToDec();
	string QIntToHex();

	friend int setBit1(int& data, int offset);
	friend int getBit(int data, int offset);

	friend QInt binToQInt(std::string bin);

	friend void ScanQInt(std::istream& in, QInt& x, int base);
	friend void PrintQInt(std::ostream& out, QInt x, int base);
};