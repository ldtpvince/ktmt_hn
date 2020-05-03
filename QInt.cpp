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
string DecToBin(QInt x)
{
	string bits(128,' ');
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 32; j++)
		{
			if (x.getBit(x.data[i], j) == 1)
				bits[i * 32 + j] = '1';
			else bits[i * 32 + j] = '0';
		}
	return bits;
}

QInt BinToDec(string bits)
{
	QInt Result;
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 32; j++)
			if (bits[i * 32 + j] == 1)
				Result.data[i] = QInt::setBit(Result.data[i], j);
	return Result;
}

QInt QInt::operator +(const QInt& x) const
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

QInt QInt::operator -(const QInt& x) const
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

QInt QInt::operator* (const QInt& x) const
{
	//Kiem tra nhan voi 0
	if ((*this) == QInt::zero() || x == QInt::zero())
		return QInt();

}

QInt QInt::operator/ (const QInt& x) const
{

}

//Cac toan tu so sanh va gan
bool QInt::operator> (const QInt& x) const
{
	bool isANegative = (*this).isNegative();
	bool isxNegative = x.isNegative();
	//Hai so trai dau
	if (isANegative != isxNegative)
	{
		return (isANegative == false);
	}

	string a = DecToBin(*this), b = DecToBin(x);
	//Hai so cung dau
	int index = 1;
	while (a[index] == b[index])index++;
	return (a[index] == '1');
}

bool QInt::operator< (const QInt& x) const
{
	bool isANegative = (*this).isNegative();
	bool isxNegative = x.isNegative();
	//Hai so trai dau
	if (isANegative != isxNegative)
	{
		return (isANegative == true);
	}

	string a = DecToBin(*this), b = DecToBin(x);
	//Hai so cung dau
	int index = 1;
	while (a[index] == b[index])index++;
	return (a[index] == '0');
}

bool QInt::operator== (const QInt& x) const
{
	for (int i = 0; i < QINT_LENGTH; i++)
		if ((*this).data[i] != x.data[i])
			return false;
	return true;
}

bool QInt::operator!= (const QInt& x) const
{
	// Phu dinh cua toan tu bang
	return !((*this) == x);
}

bool QInt::operator>= (const QInt& x) const
{
	//Phu dinh toan tu be hon
	return !((*this) < x);
}

bool QInt::operator<= (const QInt& x) const
{
	//Phu dinh toan tu lon hon
	return !((*this) > x);
}

QInt& QInt::operator= (const QInt& x)
{
	for (int i = 0; i < QINT_SIZE; i++)
		(*this).data[i] = x.data[i];
	return (*this);
}

//Toan tu logic
QInt QInt::operator& (const QInt& x) const
{
	QInt Ketqua;
	for (int i = 0; i < 4; i++)
		Ketqua.data[i] = ((*this).data[i] & x.data[i]);
	return Ketqua;
}

QInt QInt::operator| (const QInt& x) const
{
	QInt Ketqua;
	for (int i = 0; i < 4; i++)
		Ketqua.data[i] = ((*this).data[i] | x.data[i]);
	return Ketqua;
}

QInt QInt::operator^ (const QInt& x) const
{
	QInt Ketqua;
	for (int i = 0; i < 4; i++)
		Ketqua.data[i] = ((*this).data[i] ^ x.data[i]);
	return Ketqua;
}

QInt QInt::operator~ () const
{
	QInt Ketqua;
	for (int i = 0; i < 4; i++)
		Ketqua.data[i] = (~(*this).data[i]);
	return Ketqua;
}

QInt QInt::operator <<(int index) const
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

QInt QInt::operator >>(int index) const
{
	// Chuyen QInt ve day bit
	string a = DecToBin(*this);
	//Ghi lai bit dau
	char bit_dau = a[0];
	a = a.substr(0, 128 - index);
	string b(index, bit_dau);
	a = b + a;
	QInt Result = BinToDec(a);
	return Result;
}

QInt QInt::rol(int nums) const
{
	// Chuyen QInt ve day bit
	string a = DecToBin(*this);
	//Ghi lai cac bit ben trai
	string left = a.substr(0, nums);
	a = a.substr(nums);
	// Chuyen nums bit trai ve cuoi
	a = a + left;
	QInt Result = BinToDec(a);
	return Result;
}

QInt QInt::ror(int nums) const
{
	// Chuyen QInt ve day bit
	string a = DecToBin(*this);
	//Ghi lai cac bit ben phai
	string right = a.substr(128 - nums);
	a = a.substr(0, 128 - nums);
	// Chuyen nums bit phai len dau
	a = right + a;
	QInt Result = BinToDec(a);
	return Result;
}

QInt QInt::zero()
{
	static QInt staticZero;
	static bool zeroInit = false;
	if (!zeroInit)
	{
		for (int i = 0; i < 4; i++)
			staticZero.data[i] = 0;
		zeroInit = true;
	}
	return staticZero;
}

//Kiem tra QInt la so am hay khong
bool QInt::isNegative() const
{
	// Kiem tra bit dau tien
	return getBit((*this).data[0], 0) == 1;
}