#pragma once
#include <string>

using namespace std;

#define MAX_N		4
#define BIT			32
#define LEN			MAX_N*BIT
#define BIT_EXP		15
#define BIT_SIGN	112
#define BIAS		(1 << (BIT_EXP - 1)) - 1
#define MAX_EXP		(1 << (BIT_EXP - 1))
#define MIN_EXP		- (1 << (BIT_EXP - 1)) + 1

class Qfloat
{
protected:
	int data[MAX_N]; //data[0]: 127->96, data[1]: 95->64, ...
public:
	//*Cac ham khoi tao*----------------------------------------
	Qfloat();
	Qfloat(string s);
public:
	//*Cac ham ho tro*------------------------------------------
	//Kiem tra bang 0
	bool isZero() const;
	//Lay dau
	string getSigni() const;
	//Lay mu
	int getExp()const;
	//So vo cung
	static Qfloat inf(bool sign);
public:
	//Lay bit
	bool getBit(int index) const;
	//Gan bit
	void setBit(int index, bool bit);
	//*Cac ham bai tap yeu cau*--------------------------------
	//Nhap so thuc
	static void ScanQfloat(Qfloat& x, string s, int base);
	//Xuat so thuc
	static string PrintQfloat(Qfloat x, int base);
	//Chuyen doi Qfloat nhi phan sang thap phan
	static Qfloat BinToDec(string bit);
	//Chuyen doi Qfloat thap phan sang nhi phan
	static string DecToBin(Qfloat x);
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

string toStrBias(int exp);
std::string productQfloat(std::string a, std::string b, int& exp);
