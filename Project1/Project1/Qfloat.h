#pragma once
#include <string>

using namespace std;

class Qfloat
{
protected:
	unsigned int data[4];
	//Ham khoi tao
public:
	Qfloat();
	Qfloat(string s);
	//Ham ho tro
public:
	Qfloat strBinToQfloat(string s);
public:
	//Nhap so thuc
	static void ScanQfloat(Qfloat& x);
	//Xuat so thuc
	static void PrintQfloat(Qfloat x);
	//Chuyen doi Qfloat nhi phan sang thap phan
	Qfloat BinToDec(bool* bit);
	//Chuyen doi Qfloat thap phan sang nhi phan
	bool* DecToBin(Qfloat x);
};

