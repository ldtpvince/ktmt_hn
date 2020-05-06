#pragma once
#include <string>

using namespace std;

#define MAX_N		4
#define BIT			32
#define BIT_EXP		15
#define BIT_SIGN	112
#define MAX_EXP		(1 << (BIT_EXP - 1)) - 1
#define MIN_EXP		- (1 << (BIT_EXP - 1)) + 2

class Qfloat
{
protected:
	int data[MAX_N];
public:
	//*Cac ham khoi tao*----------------------------------------
	Qfloat();
	Qfloat(string s);
protected:
	//*Cac ham ho tro*------------------------------------------
	//Kiem tra chuoi co toan ky tu da cho khong
	bool checkStr(string s, char c);
	//Chuyen sang chuoi he thap phan
	string toStrDec();
	//Kiem tra bang 0
	bool isZero() const;
	//Lay bit
	bool getBit(int index) const;
	//Gan bit
	void setBit(int index, bool bit);
	//Lay dau
	string getSigni() const;
	//Lay mu
	int getExp()const;
	//So vo cung
	Qfloat inf(bool sign);
public:
	//*Cac ham bai tap yeu cau*--------------------------------
	//Nhap so thuc
	static void ScanQfloat(Qfloat& x);
	//Xuat so thuc
	static void PrintQfloat(Qfloat x);
	//Chuyen doi Qfloat nhi phan sang thap phan
	Qfloat BinToDec(string bit);
	//Chuyen doi Qfloat thap phan sang nhi phan
	string DecToBin(Qfloat x);
public:
	//Phep gan Qfloat = Qfloat
	Qfloat& operator=(const Qfloat&);
	//Phep gan Qfloat = string
	Qfloat& operator =(string s);
	//Phep cong
	Qfloat operator+(const Qfloat&);
	//Phep tru
	Qfloat operator-(const Qfloat&);
	//Phep nhan
	Qfloat operator*(const Qfloat&);
	//Phep chia
	Qfloat operator/(const Qfloat&);
};

