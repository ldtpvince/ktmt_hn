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

	friend int setBit1(int& data, int offset);
	friend int getBit(int data, int offset);

	friend bool* DecToBin(QInt x);
	friend QInt binToQInt(std::string bin);

	friend void ScanQInt(std::istream& in, QInt& x, int base);
	friend void PrintQInt(std::ostream& out, QInt x, int base);
};