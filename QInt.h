#pragma once

class QInt {
private:
	int data[4];

public:
	QInt(int m_data[])
	{
		for (int i = 0; i < 4; i++)
			data[i] = m_data[i];

	}
	QInt();

	static int setBit(int& data, int offset);
	static int getBit(int data, int offset);

	friend void scanQInt(QInt& x);
	friend void printQInt(QInt x);

	friend std::string DecToBin(QInt x);
	QInt BinToDec(std::string bits);

	QInt operator +(const QInt& x);
	QInt operator -(const QInt& x);

	// Phep dich bit
	QInt operator <<(int index);
	QInt operator >> (int index) const;
};