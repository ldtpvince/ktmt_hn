#pragma once
#include <string>

using namespace std;

class Qfloat
{
private:
	unsigned int data[4];
	//*Cac ham khoi tao*
public:
	Qfloat();
	Qfloat(string s);
	//*Cac ham ho tro*
	//Toan tu gan: Qfloat = string
	Qfloat& operator =(string s);
protected:
	//Sao chep du lieu vao data
	void updateData(unsigned int other[4]);
	//Kiem tra phan tri bang 0
	bool checkSignificandEqualZero();
public:
	//*Cac ham bai tap yeu cau*
	//Nhap so thuc
	static void ScanQfloat(Qfloat& x);
	//Xuat so thuc
	static void PrintQfloat(Qfloat x);
	//Chuyen doi Qfloat nhi phan sang thap phan
	Qfloat BinToDec(string bit);
	//Chuyen doi Qfloat thap phan sang nhi phan
	string DecToBin(Qfloat x);
};

