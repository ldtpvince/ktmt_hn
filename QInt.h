#pragma once
#define QINT_SIZE 16
#define QINT_LENGTH 4

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
	friend QInt BinToDec(std::string bits);

	//Cac toan tu 
	QInt operator +(const QInt& x) const;
	QInt operator -(const QInt& x) const;
	QInt operator* (const QInt& x) const;
	QInt operator/ (const QInt& x) const;

	//Cac toan tu so sanh va gan
	bool operator> (const QInt& x) const;
	bool operator< (const QInt& x) const;
	bool operator== (const QInt& x) const;
	bool operator!= (const QInt& x) const;
	bool operator>= (const QInt& x) const;
	bool operator<= (const QInt& x) const;
	QInt& operator= (const QInt& x);

	// Cac toan tu logic
	QInt operator& (const QInt& x) const;
	QInt operator| (const QInt& x) const;
	QInt operator^ (const QInt& x) const;
	QInt operator~ () const;

	// Phep dich bit
	QInt operator <<(int index) const;
	QInt operator >>(int index) const;
	//Phep xoay
	QInt rol(int nums) const;
	QInt ror(int nums) const;

	//Ham con
	static QInt zero();
	bool isNegative() const;
};