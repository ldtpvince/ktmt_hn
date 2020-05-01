#pragma once
#include <iostream>

class QInt {
private:
	int data[4];
	int binLen;

public:
	QInt();

	friend int setBit1(int& data, int offset);
	friend int getBit(int data, int offset);

	friend void ScanQInt(std::istream& is, QInt& x, int base);
	friend void PrintQInt(QInt x);
};