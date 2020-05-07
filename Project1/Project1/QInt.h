#pragma once
#include <iostream>
#include <string>
#include <istream>
#include <ostream>

#define QINT_SIZE 32
#define QINT_LENGTH 4

class QInt {
private:
	int data[4];
	int binLen;

public:
	QInt();
	QInt(std::string dec);
	QInt(unsigned int dec);

	// Cac ham chuyen doi
	int QIntBinSize();
	std::string toSignedNumber(bool& sign);

	std::string QIntToStrDec();
	friend std::string DecToBin(QInt x);
	friend QInt BinToDec(std::string bits);
	friend std::string BinToHex(std::string hex);
	friend std::string DecToHex(QInt x);
	friend std::string DecTo128Bin(QInt x);


	friend void ScanQInt(std::istream& in, QInt& x, int base);
	friend void PrintQInt(std::ostream& out, QInt x, int base);

	//Cac toan tu 
	QInt operator+ (const QInt& x) const;
	QInt operator- (const QInt& x) const;
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

	//CAC HAM PHU
	//Khoi tao QInt = 0
	static QInt zero();
	static QInt negativeOne();
	static QInt min();

	//Kiem tra QInt co la so am hay khong
	bool isNegative() const;

	static int setBit0(int& data, int offset);
	static int setBit1(int& data, int offset);
	static int getBit(int data, int offset);
	int getBitAt(int pos);
	void setBitAt(int pos, bool type);

	//Ham chia lay nguyen va du va ham cong, tru 2 so QInt khong kiem tra tran so
	QInt divide(const QInt& div, QInt& r) const;
	friend QInt plusQInt(const QInt & x, const QInt & y);
	friend QInt substractQInt(const QInt & x, const QInt & y);
};

QInt BinToDec(std::string bin);
std::string strDecToBin(std::string dec);