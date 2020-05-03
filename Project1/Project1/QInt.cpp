#include "QInt.h"
using namespace std;

QInt::QInt() {
	for (int i = 0; i < 4; i++) {
		data[i] = 0;
	}
	binLen = 0;
}

bool isNegativeDec(string& dec) {
	if (dec[0] == '-') {
		dec.erase(0, 1);
		return true;
	}
	return false;
}

bool isNegativeBin(string bin) {
	if (bin[0] == '1') {
		return true;
	}
	return false;
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
			result.push_back(temp / 2 + '0');
			temp = temp % 2;
		}
		else {
			temp = temp * 10 + src[i] - '0';
		}
	}

	return result;
}

int setBit1(int& data, int offset) {
	data = (data | (1 << (31 - offset)));
	return 0;
}

int getBit(int data, int offset) {
	return (data >> (31 - offset) & 1);
}

// ------------------------------------------------------Ham scan----------------------------------------------------

// Ham chuyen mot ki tu so thap luc phan thanh ki tu thap phan
string charHexToDec(char hex) {
	string result;
	if (hex >= '0' && hex <= '9') {
		result.push_back(hex);
		return result;
	}
	if (hex >= 'A' && hex <= 'F') {
		result.push_back('1');
		result.push_back(hex - 'A' + '0');
		return result;
	}
	return result;
}

// Ham lap day mot so nhi phan cho du bo cac 4 bit 
string fill0ToBin(string bin) {
	string result = bin;
	int remainBit = ((bin.size() / 4) + 1) * 4 - bin.size();
	for (int i = 0; i < remainBit; i++) {
		result.insert(bin.begin(), '0');
	}
	return result;
}

// Ham chuyen mot chuoi so thap phan thanh day nhi phan bu 2
string strDecToBin(string dec) {
	string result = {};
	bool negativeFlag = isNegativeDec(dec);
	string temp = dec;	
	int numlen = dec.size();

	while (numlen > 1 || temp[0] >= 1) {
		if (temp[numlen - 1] % 2 == 1) {
			result.insert(result.begin(), '1');
		}
		else {
			result.insert(result.begin(), '0');
		}
		temp = div2Dec(temp);
		numlen = temp.size();
	}

	if (negativeFlag) { 
		bool first1Bit = false;
		for (int i = result.size() - 1; i >= 0; i--) {
			if (result[i] == '1' && !first1Bit) {
				first1Bit = true;
				continue;
			}
			if (first1Bit) {
				result[i] = ~((result[i] - '0') | 0) + '0';
			}
		}
		for (int i = 128 - result.size(); i > 0; i--) {
			result.insert(result.begin(), '1');
		}
	}

	return result;
}

// Ham chuyen mot chuoi so thap luc phan thanh nhi phan bu 2
string strHexToBin(string hex) {
	// Ki tu dau tien trong chuoi thap luc phan khong can phai chuyen thanh bo 4 bit nhi phan
	string result = strDecToBin(charHexToDec(hex[0]));

	// Dau tien la chuyen tung ki tu thap luc phan thanh thap phan, roi chuyen thap phan sang cac bo 4 bit nhi phan
	for (int i = 1; i < hex.size(); i++) {
		string decStr = charHexToDec(hex[i]);
		result = result + fill0ToBin(strDecToBin(decStr));
	}

	return result;
}

// Ham nhap mot chuoi so nhi phan thanh so QInt
QInt binToQInt(string bin) {
	QInt result;

	for (int i = bin.size() - 1 ; i  >= 0; i--) {
		if (bin[i] == '1') {
			setBit1(result.data[3 - (bin.size() - i - 1) / 32], 31 - bin.size() + 1 + i);
		}
	}
	result.binLen = bin.size();

	return result;
}

// Ham nhap mot chuoi so va luu vao QInt voi co so tuong ung
void ScanQInt(istream& in, QInt& x, int base) {
	string temp;
	in >> temp;
	int numlen = temp.size();

	switch (base) {
	case 2: {
		x = binToQInt(temp);
		break;
	}
	case 10: {
		x = binToQInt(strDecToBin(temp));
		break;
	}
	case 16: {
		x = binToQInt(strHexToBin(temp));
		break;
	}
	}
}

// ------------------------------------------------------Ham print----------------------------------------------------

string QInt::QIntToBin() {
	string result;
	for (int i = 0; i < binLen; i++) {

	}
}
// Gom 3 ham chuyen tu QInt -> string nhi phan -> chuyen qua cac co so khac nhu thap phan hay thap luc phan
void PrintQInt(std::ostream& out, QInt x, int base) {
	string result;

	switch (base) {
	case 2: {
		for (int i = 0; i < x.binLen; i++) {
			result.push_back(getBit(x.data[i / 32], i % 32));
		}
		break;
	}
	case 10: {
		break;
	}
	}

	out << result;
}

//Ham chuyen doi tu thap phan sang nhi phan
string DecToBin(QInt x)
{
	string bits(128, ' ');
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
				Result.data[i] = QInt::setBit1(Result.data[i], j);
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

QInt QInt::operator >> (int index) const
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

int QInt::setBit1(int& data, int offset) {
	return (data | (1 << (31 - offset)));
}

//Tra ve gia tri cua bit thu offset
int QInt::getBit(int data, int offset) {
	return (data >> (31 - offset) & 1);
}