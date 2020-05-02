#include <iostream>
#include <string>
#include "QInt.h"
#include <conio.h>

using namespace std;

//Khoi tao mac dinh
QInt::QInt()
{
	data[0] = data[1] = data[2] = data[3] = 0;
}

string div2Dec(string src) {
	string result;
	int temp = 0;

	for (int i = 0; i < src.size(); i++) {
		if (src[i] >= '2') {
			temp = temp * 10 + src[i] - '0';
			result.push_back(temp / 2 + '0');
			temp = src[i] % 2;
			continue;
		}
		if (src[i] < '2' && i > 0) {
			temp = temp * 10 + src[i] - '0';
			result.push_back('0');
		}
		else {
			temp = temp * 10 + src[i] - '0';
		}
	}

	return result;
}

int QInt::setBit(int& data, int offset) {
	return (data | (1 << (31 - offset)));
}

//Tra ve gia tri cua bit thu offset
int QInt::getBit(int data, int offset) {
	return (data >> (31 - offset) & 1);
}

void ScanQInt(QInt& x) {
	string temp;
	getline(cin, temp);
	int numlen = temp.size();

	while (numlen > 1) {

	}
}

//Ham chuyen doi tu thap phan sang nhi phan
//string DecToBin(QInt x)
//{
//	string bits(128,' ');
//	for (int i = 0; i < 4; i++)
//		for (int j = 0; j < 32; j++)
//		{
//			if (x.getBit(x.data[i], j) == 1)
//				bits[i * 32 + j] = '1';
//			else bits[i * 32 + j] = '0';
//		}
//	return bits;
//}
//
//QInt QInt::BinToDec(string bits)
//{
//	QInt Result;
//	for (int i = 0; i < 4; i++)
//		for (int j = 0; j < 32; j++)
//			if (bits[i * 32 + j] == 1)
//				Result.data[i] = QInt::setBit(Result.data[i], j);
//	return Result;
//}

QInt QInt::operator +(const QInt& x)
{
	string Kqua(128, ' ');
	string a = DecToBin(*this), b = DecToBin(x);
	// Bit nho
	char bit_Nho = '0';
	for (int i = 0; i < 128; i++)
	{
		if (a[i] == b[i])
		{
			if (a[i] == '0')
				Kqua[i] = bit_Nho, bit_Nho = '0';
			else
				Kqua[i] = bit_Nho, bit_Nho = '1';
		}
		else
		{
			if (bit_Nho = '0')
				Kqua[i] = '1', bit_Nho = '0';
			else
				Kqua[i] = '0', bit_Nho = '1';
		}
	}
	QInt Result = BinToDec(Kqua);
	return Result;
}

QInt QInt::operator -(const QInt& x)
{
	string Kqua(128, ' ');
	string a = DecToBin(*this), b = DecToBin(x);
	// Bit nho
	char bit_Nho = '0';
	for (int i = 0; i < 128; i++)
	{
		if (a[i] == b[i])
		{
			if (bit_Nho == '0')
				Kqua[i] = bit_Nho = '0';
			else
				Kqua[i] = bit_Nho = '1';
		}
		else
		{
			if (a[i] = '0')
			{
				if (bit_Nho = '1')
					Kqua = '0', bit_Nho = '1';
				else
					Kqua = bit_Nho = '1';
			}
			else if (a[i] = '0')
			{
				if (bit_Nho = '1')
					Kqua = '0', bit_Nho = '1';
				else
					Kqua = bit_Nho = '1';
			}
		}
	}
	QInt Result = BinToDec(Kqua);
	return Result;
}

QInt QInt::operator <<(int index)
{
	// Chuyen QInt ve day bit
	string a = DecToBin(*this);
	//Ghi lai bit dau
	char bit_dau = a[0];
	a = a.substr(index);
	string b(index, '0');
	a = a + b;
	// Gan lai bit dau
	a[0] = bit_dau;
	QInt Result = BinToDec(a);
	return Result;
}

QInt QInt::operator <<(int index)
{
	// Chuyen QInt ve day bit
	string a = DecToBin(*this);
	//Ghi lai bit dau
	char bit_dau = a[0];
	a = a.substr(index);
	string b(index, '0');
	a = a + b;
	// Gan lai bit dau
	a[0] = bit_dau;
	QInt Result = BinToDec(a);
	return Result;
}

QInt QInt::operator >>(int index)
{
	// Chuyen QInt ve day bit
	string a = DecToBin(*this);
	//Ghi lai bit dau
	char bit_dau = a[0];
	a = a.substr(0, 128 - index);
	string b(index, bit_dau);
	a = b + a;
	// Gan lai bit dau
	a[0] = bit_dau;
	QInt Result = BinToDec(a);
	return Result;
}


int main() {
	cout << div2Dec("4");

	getchar();
	return 0;
}