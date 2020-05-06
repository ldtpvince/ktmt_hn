#include "Qfloat.h"
#include <iostream>
#include "QInt.h"

//bias 15 bit
const unsigned int bias = 16383;
//day bit 01111111111111110000000000000000 khong dau
const unsigned int layMu = 2147418112;
//day bit 00000000000000001111111111111111 khong dau
const unsigned int layTri = 65535;		

//Dich chuyen sang phai
string shrSigni(string s, int val) {
	for (int i = 0; i < val; i++)
		s = '0' + s;
	return s;
}

//Dich chuyen sang trai
string shlSigni(string s, int val) {
	for (int i = 0; i < val; i++)
		if (s.length() > 0)
			s.erase(0, 1);
	return s;
}

//Chuyen sang QInt
QInt toQInt(string s, bool sign) {
	QInt result;
	result = BinToDec(s);
	if (sign)
		result = -result;
	return 0;
}

//Cong phan tri
string addSigni(string a, string b, bool sign_a, bool sign_b, bool& sign) {
	QInt signi1, signi2, sum;
	string result;
	signi1 = toQInt(a, sign_a);
	signi2 = toQInt(b, sign_b);
	sum = signi1 + signi2;
	result = sum.toSignedNumber(sign);
	return result;
}

//Chinh sua phan tri: do dai 128 bit, khong tran so
int editSigni(string s) {
	int result = 0;
	if (s[0] == '1') {
		s = shrSigni(s, 1);
		result++;
		s.erase(0, 1);
	}
	else {
		s.erase(0, 1);
		while (s[0] == '0') {
			s.erase(0, 1);
			result--;
		}
	}
	while (s.length() > BIT_SIGN)
		s.erase(s.length() - 1, 1);
	return result;
}

string toStrBias(int exp) {
	exp = exp + MAX_EXP - 1;
	string result;
	for (int i = 0; i < BIT_EXP; i++)
		result += ('0' + (exp >> i) & 1);
	return result;
}

//Chia chuoi so nguyen duong cho 2
string strDecDiv2(string s) {
	string res;
	int temp = 0;
	for (int i = 0; i < s.length(); i++) {
		temp = temp * 10 + (s[i] - '0');
		if (i > 0 || (i == 0 & temp > 1))
			res.push_back((temp / 2) + '0');
		temp %= 2;
	}
	return res;
}

//Chuyen chuoi so nguyen duong thanh chuoi nhi phan
string strDecToStrBin(string s) {
	string res;
	while (s != "") {
		res.push_back((s[s.length() - 1] - '0') % 2 + '0');
		s = strDecDiv2(s);
	}
	reverse(res.begin(), res.end());
	return res;
}

//Chuyen doi so thap phan thanh chuoi nhi phan 15 bit
string decToStrBin(int dec) {
	string res;
	while (dec != 1) {
		res.push_back((dec % 2) + '0');
		dec /= 2;
	}
	res.push_back('1');
	while (res.length() < 15)
		res.push_back('0');
	reverse(res.begin(), res.end());
	return res;
}

//Nhan so thuc 0.s voi 2, lay phan nguyen
bool layBit(string& s) {
	bool temp = 0;
	string sClone;
	for (int i = s.length() - 1; i >= 0; i--) {
		int kq = (s[i] - '0') * 2 + temp;
		sClone.push_back(kq % 10);
		temp = kq / 10;
	}
	return (temp == 1);
}

//Chuyen chuoi 32 bit thanh so nguyen khong dau
unsigned int strBinToDec(string s) {
	unsigned int res = 0;
	int temp = 1;
	for (int i = 0; i < s.length(); i--)
		res = res * 2 + (s[i] - '0');
	return res;
}

//Khoi tao khong tham so
Qfloat::Qfloat() {
	for (int i = 0; i < MAX_N; i++)
		this->data[i] = 0;
}

//Khoi tao tu chuoi so thuc
Qfloat::Qfloat(string s) {
	string res;
	if (s[0] == '-') {
		res = "1";
		s.erase(0, 1);
	}
	else
		res = "0";
	while (s[s[0]] == '0')
		s.erase(0, 1);
	while (s[s.length() - 1] == '0')
		s.erase(s.length() - 1, 1);
	int pos = s.find('.');
	string temp = strDecToStrBin(s.substr(0, pos));
	if (temp == "")
		res += "111111111111111"; 
	else {
		int exponent = bias + temp.length() - 1;
		res += decToStrBin(exponent);
	}
	//Can cap nhat error
	res += temp;
	temp = s.substr(pos + 1, s.length() - pos);
	while (res.length() < 128)
		res.push_back(layBit(s));
	*this = res;
}

//Kiem tra chuoi co toan ky tu da cho khong
bool Qfloat::checkStr(string s, char c) {
	for (int i = 0; i < s.length(); i++)
		if (s[i] != c)
			return false;
	return true;
}

//Kiem tra bang 0
bool Qfloat::isZero() const {
	for (int i = 0; i < MAX_N * BIT - 1; i++)
		if (this->getBit(i))
			return false;
	return true;
}

//Lay bit
bool Qfloat::getBit(int index) const {
	return (this->data[MAX_N - 1 - (index / BIT)] >> (index % 32) & 1);
}

//Gan bit
void Qfloat::setBit(int index, bool bit) {
	int i = MAX_N - 1 - (index / BIT);
	int pos = index % 32;
	if (bit)
		this->data[i] = this->data[i] | (1 << pos);
	else
		this->data[i] = this->data[i] & ~(1 << pos);
}

//Lay dau
string Qfloat::getSigni() const {
	string result;
	for (int i = BIT_SIGN - 1; i >= 0; i++)
		result += this->getBit(i);
	return result;
}

//Lay mu
int Qfloat::getExp()const {
	int result = -((1 << (BIT_EXP - 1)) - 1); //bias
	for (int i = 0; i < BIT_EXP; i++)
		if (this->getBit(MAX_N * BIT - BIT_EXP - 1 + i) == 1)
			result += (1 << i);
	return result;
}

//So vo cung
Qfloat Qfloat::inf(bool sign) {
	Qfloat result;
	result.data[0] = (~(1 << BIT_EXP)) << BIT - BIT_EXP - 1;
	return result;
}

//Toan tu gan: Qfloat = string
Qfloat& Qfloat::operator =(string s) {
	Qfloat res = s;
	for (int i = 0; i < 4; i++)
		res.data[i] = strBinToDec(s.substr(32 * i, 32));
	return res;
}

//Nhap so thuc
void Qfloat::ScanQfloat(Qfloat& x) {
	string s;
	getline(cin, s);
	Qfloat temp = s;
	x = s;
}

//Xuat so thuc
void Qfloat::PrintQfloat(Qfloat x) {

}

//Chuyen doi Qfloat nhi phan sang thap phan
Qfloat Qfloat::BinToDec(string bit) {
	Qfloat res;
	for (int i = 0; i < 4; i++)
		res.data[i] = strBinToDec(bit.substr(32 * i, 32));
	return res;
}

//Chuyen doi Qfloat thap phan sang nhi phan
string Qfloat::DecToBin(Qfloat x) {
	string res;
	for (int i = 3; i >= 0; i++)
		res += decToStrBin(this->data[i]);
	return res;
}

string Qfloat::toStrDec() {
	string res;
	string strBin = DecToBin(*this);
	string strExp = strBin.substr(1, 15);
	string strSigni = strBin.substr(16, 112);
	if (strBin[0] == '1')
		res += "-";

	if (checkStr(strExp, '0')) {
		if (checkStr(strSigni, '0'))
			return "0";
		else
			return "DENORMALIZED";
	}
	else {
		if (checkStr(strSigni, '0'))
			return res + "Inf";
		else
			return "NaN";
	}
	unsigned int exp = stoi(strExp, nullptr, 2);
	exp -= bias;

	//Tim phan nguyen, thap phan o he nhi phan
	string strInt = "1";
	string strFrac = strSigni;
	while (exp != 0) {
		if (exp < 0) {
			strFrac = strInt[strInt.length() - 1] + strFrac;
			strInt.erase(strInt.length() - 1, 1);
			strInt = '0' + strInt;
			exp++;
		}
		else {
			strInt += strFrac[0];
			strFrac.erase(0, 1);
			strFrac += '0';
			exp--;
		}
	}

	while (strInt.length() > 1 && strInt[0] == '0')
		strInt.erase(0, 1);
	while (strFrac.length() > 1 && strFrac[strFrac.length() - 1] == '0')
		strFrac.erase(strFrac.length() - 1, 1);

	//Cai dat tren co the cai tien them vao so 0
	
	
}

Qfloat& Qfloat::operator=(const Qfloat& other) {
	for (int i = 0; i < MAX_N; i++)
		this->data[i] = other.data[i];
	return *this;
}

Qfloat Qfloat::operator+(const Qfloat& other) {
	//Xet 1 so bang 0
	if (this->isZero())
		return other;
	if (other.isZero())
		return *this;
	//Lay gia tri mu
	int e1, e2, e;
	e1 = this->getExp();
	e2 = other.getExp();
	//Lay phan tri
	string s1, s2;
	s1 = '1' + this->getSigni();
	s2 = '1' + other.getSigni();
	//So sanh mu
	int dist = e1 - e2;
	if (dist < 0) {
		s1 = shrSigni(s1, -dist);
		e = e2;
	}
	else {
		s2 = shrSigni(s1, dist);
		e = e1;
	}
	//Lay dau
	bool sign1, sign2, sign;
	sign1 = this->getBit(MAX_N * BIT - 1);
	sign2 = other.getBit(MAX_N * BIT - 1);
	sign = 0;
	string strSigni = addSigni(s1, s2, sign1, sign2, sign);
	Qfloat zero;
	if (checkStr(strSigni, '0'))
		return zero;
	int temp = editSigni(strSigni);
	e += temp;
	if (e < MIN_EXP)
		return zero;
	if (e > MAX_EXP)
		return inf(sign);
	string strExp = toStrBias(e);
	char Sign;
	if (sign)
		Sign = '1';
	else
		Sign = '0';
	string result = Sign + strExp + strSigni;
	return result;
}

Qfloat Qfloat::operator-(const Qfloat& other) {
	Qfloat temp = other;
	if (temp.getBit(0))
		temp.setBit(0, 0);
	else
		temp.setBit(0, 1);
	return (*this) + temp;
}

Qfloat Qfloat::operator*(const Qfloat& other) {

}

Qfloat Qfloat::operator/(const Qfloat& other) {

}