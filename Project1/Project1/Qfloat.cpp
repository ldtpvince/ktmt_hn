#include "Qfloat.h"
#include <iostream>
#include "QInt.h"
#include <sstream>

//bias 15 bit
const unsigned int bias = 16383;
//day bit 01111111111111110000000000000000 khong dau
const unsigned int layMu = 2147418112;
//day bit 00000000000000001111111111111111 khong dau
const unsigned int layTri = 65535;		

//Kiem tra chuoi co toan ky tu da cho khong
bool checkStr(string s, char c) {
	for (int i = 0; i < s.length(); i++)
		if (s[i] != c)
			return false;
	return true;
}

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
	QInt zero;
	result = BinToDec(s);
	if (sign)
		result = zero - result;
	return 0;
}

//Cong phan tri
string addSigni(string a, string b, bool sign_a, bool sign_b, bool& sign) {
	QInt signi1, signi2, sum;
	string result;
	signi1 = toQInt(a, sign_a);
	signi2 = toQInt(b, sign_b);
	sum = signi1 + signi2;
	//result = sum.toSignedNumber(sign);
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
string toBinExp(int dec) {
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

//Nhan day thap phan voi 2
bool mul2(string& s) {
	bool temp = 0; //Bien nho
	string result;
	for (int i = s.length() - 1; i >= 0; i--) {
		int kq = (s[i] - '0') * 2 + temp;
		result.push_back(kq % 10 + '0');
		temp = kq / 10;
	}
	while (result[0] == '0' && result.length() > 1)
		result.erase(0, 1);
	reverse(result.begin(), result.end());
	s = result;
	return (temp == 1);
}

//Khoi tao khong tham so
Qfloat::Qfloat() {
	for (int i = 0; i < MAX_N; i++)
		this->data[i] = 0;
}

//Chuyen tu chuoi thap phan sang Qfloat
Qfloat strDecToQfloat(string s) {
	Qfloat result;//Khoi tao result=0
	//Xet s = 0
	if (s == "0")
		return result;
	//Xet dau
	if (s[0] == '-') {
		result.setBit(MAX_N * BIT - 1, '1');
		s.erase(0, 1);
	}
	//Xet chuoi nguyen
	if (s.find('.', 0) == string::npos)
		s += ".0";
	//Tach phan nguyen va phan thap phan
	int pos = s.find('.');
	string Int = s.substr(0, pos);
	string Frac = s.substr(pos + 1, s.length() - pos - 1);
	//Chuan hoa
	while (Int.length() > 1 && Int[0] == '0')
		Int.erase(0, 1);
	while (Frac.length() > 1 && Frac[Frac.length() - 1] == '0')
		Frac.erase(Frac.length() - 1, 1);
	string strExp;
	string strSigni;
	//Xet phan nguyen khac 0
	if (Int != "0") {
		//Doi phan nguyen
		QInt temp;
		istringstream istr(Int);
		ScanQInt(istr, temp, 10);
		string binInt = DecToBin(temp);
		//Lay exp va khoi tao strSigni neu phan nguyen chuyen sang phan tri
		int exp = binInt.length() - 1;
		if (exp > 0)
			strSigni = binInt.substr(1, exp);
		exp += BIAS;
		strExp = toBinExp(exp);
	}
	else {
		int exp = 0;
		while (1) {
			exp--;
			if (mul2(Frac))
				break;
		}
		exp += bias;
		strExp = toBinExp(exp);
	}
	while (strSigni.length() < BIT_SIGN) {
		if (mul2(Frac))
			strSigni += '1';
		else
			strSigni += '0';
		if (checkStr(Frac, '0'))
			break;
	}
	while (strSigni.length() < BIT_SIGN)
		strSigni += '0';
	for (int i = 0; i < BIT_EXP; i++)
		result.setBit(LEN - 2 - i, strExp[i] == '1');
	for (int i = 0; i < BIT_SIGN; i++)
		result.setBit(LEN - 2 - BIT_EXP - i, strSigni[i] == '1');
	return result;
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

string mulByHalf(string s, bool con)
{
	string result = "";
	int carry = 0;
	for (int i = s.length() - 1; i >= 0; i--) {
		int temp = s[i] - '0';
		temp = temp * 5 + carry;
		result += (temp % 10 + '0');
		carry = temp / 10;
	}
	result += (carry + '0');

	reverse(result.begin(), result.end());
	if (con)
		result[0] = result[0] + 5;

	while (result.length() > 1 && result[result.length() - 1] == '0')
		result.erase(result.length() - 1, 1);
	return result;
}

//Chuyen Qfloat sang chuoi thap phan
string toStrDec(Qfloat x) {
	string result;
	string strBin = Qfloat::DecToBin(x);
	string strExp = strBin.substr(1, 15);
	string strSigni = strBin.substr(16, 112);
	if (strBin[0] == '1')
		result += "-";

	if (checkStr(strExp, '0')) {
		if (checkStr(strSigni, '0'))
			return "0";
		else
			return result + "DENORMALIZED";
	}
	else
		if (checkStr(strExp, '0')) {
			if (checkStr(strSigni, '0'))
				return result + "Inf";
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
	//Chuyen doi phan nguyen sang he 10
	QInt tempInt = BinToDec(strInt);
	string Int = tempInt.QIntToStrDec();
	//Chuyen doi phan thap phan sang he 10
	string Frac;
	int pos = strFrac.find_last_of('1');
	//Kiem tra phan thap phan khac 0
	if (pos != string::npos) {
		Frac = "5";
		for (int i = pos - 1; i >= 0; i--)
			Frac = mulByHalf(Frac, strFrac[i] == '1');
		Frac = '.' + Frac;
	}
	result = result + Int + Frac;
	return result;
}

//Khoi tao tu chuoi so thuc
Qfloat::Qfloat(string s) {
	(*this) = strDecToQfloat(s);
}

//Nhap so thuc
void Qfloat::ScanQfloat(Qfloat& x, string s, int base) {
	if (base == 2)
		x = BinToDec(s);
	else
		if (base == 10) {
			Qfloat temp = s;
			x = s;
		}
}

//Xuat so thuc
string Qfloat::PrintQfloat(Qfloat x, int base) {
	if (base == 2)
		return DecToBin(x);
	else 
		if (base==10)
			return toStrDec(x);
}

//Chuyen doi Qfloat nhi phan sang thap phan
Qfloat Qfloat::BinToDec(string s) {
	Qfloat res;
	for (int i = 0; i < s.length(); i++)
		res.setBit(MAX_N * BIT - 1 - i, s[i] == '1');
	return res;
}

//Chuyen doi Qfloat thap phan sang nhi phan
string Qfloat::DecToBin(Qfloat x) {
	string res;
	for (int i = MAX_N * BIT - 1; i >= 0; i--)
		if (x.getBit(i))
			res += '1';
		else
			res += '0';
	return res;
}

//Toan tu gan: Qfloat = string
Qfloat& Qfloat::operator =(string s) {
	Qfloat res = s;
	(*this) = res;
	return (*this);
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
	Qfloat result;
	return result;
}

Qfloat Qfloat::operator/(const Qfloat& other) {
	Qfloat result;
	return result;
}
