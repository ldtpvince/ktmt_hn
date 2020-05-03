#pragma once
#include <iostream>
#include <string>
#include <istream>
#include <ostream>

#define QINT_SIZE 16;
#define QINT_LENGTH 4;

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

	//Chuyen tu QInt sang chuoi nhi phan va nguoc lai
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
	QInt operator >> (int index) const;
	//Phep xoay
	QInt rol(int nums) const;
	QInt ror(int nums) const;

	//Ham con
	static QInt zero();
	bool isNegative() const;
	static int setBit1(int& data, int offset);
	static int getBit(int data, int offset);
};