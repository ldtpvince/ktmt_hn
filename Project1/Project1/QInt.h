#pragma once

class QInt {
private:
	int data[4];

public:
	static int setBit(int& data, int offset);
	static int getBit(int data, int offset);

	friend void scanQInt(QInt& x);
	friend void printQInt(QInt x);
};