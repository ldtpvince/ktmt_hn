#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include "QInt.h"
#include "Qfloat.h"
#include <SFML/Graphics.hpp>
#include "Game.h"

using namespace std;

//Toan tu 1 ki tu
QInt calcQInt1(QInt a, QInt b, char sign) {
	switch (sign) {
	case '+':
		return a + b;
	case '-':
		return a - b;
	case '*':
		return a * b;
	case '/':
		return a / b;
	case '&':
		return a & b;
	case '|':
		return a | b;
	case '^':
		return a ^ b;
	}
}

//Nhap QInt tu mot chuoi s voi co so base
void scanQIntFromStr(QInt& x, string s, int base) {
	istringstream operand(s);
	ScanQInt(operand, x, base);
}

//Tra ve gia tri QInt dang chuoi co so base
string printQIntToStr(QInt x, int base) {
	stringstream result;
	PrintQInt(result, x, base);
	return result.str();
}

//Toan tu dich va xoay
string calcShiftAndRotate(QInt a, int b, int pos, int base) {
	QInt result;
	switch (pos)
	{
	case 1:
		result = a << b;
		break;
	case 2:
		result = a >> b;
		break;
	case 3:
		result = a.rol(b);
		break;
	case 4:
		result = a.ror(b);
		break;
	}
	return printQIntToStr(result, base);
}

bool calcCompare(QInt a, QInt b, int pos) {
	switch (pos)
	{
	case 1:
		return a < b;
	case 2:
		return a > b;
	case 3:
		return a == b;
	case 4:
		return a <= b;
	case 5:
		return a >= b;
	}
}

//Tim xem co s trong v_s ko, neu co tra ve vi tri + 1, nguoc lai tra ve 0
int findInVector(vector<string> v_s, string s) {
	for (int i = 0; i < v_s.size(); i++)
		if (s == v_s[i])
			return i + 1;
	return 0;
}

//Xu ly QInt
string processQInt(vector<string> input) {
	//Neu la chuyen doi co so hoac toan tu 1 ngoi
	QInt a;
	if (input.size() == 3) {
		int base1 = stoi(input[0]);
		scanQIntFromStr(a, input[2], base1);
		if (input[1] == "~") {
			a = ~a;
			return printQIntToStr(a, base1);
		}
		else if (input[1] == "-") {
			QInt zero;
			a = zero - a;
			return printQIntToStr(a, base1);
		}
		int base2 = stoi(input[1]);
		return printQIntToStr(a, base2);
	}
	vector<string> shAndRo{ "<<",">>","rol","ror" };
	vector<string> compare{ "<", ">", "==", "<=", ">=" };
	//Toan tu 2 ngoi
	if (input.size() == 4) {
		int base = stoi(input[0]);
		QInt a;
		scanQIntFromStr(a, input[1], base);
		if (input[2].length() == 1) {
			QInt b;
			scanQIntFromStr(b, input[3], base);
			return printQIntToStr(calcQInt1(a, b, input[2][0]), base);
		}
		else {
			int pos = findInVector(shAndRo, input[2]);
			if (pos) {
				int b = stoi(input[3]);
				return calcShiftAndRotate(a, b, pos, base);
			}
			pos = findInVector(compare, input[2]);
			if (pos) {
				QInt b;
				scanQIntFromStr(b, input[3], base);
				if (calcCompare(a, b, pos))
					return "true";
				else
					return "false";
			}
		}
	}
}

Qfloat calcQfloat(Qfloat a, Qfloat b, char sign){
	switch (sign) {
	case '+':
		return a + b;
	case '-':
		return a - b;
	case '*':
		return a * b;
	case '/':
		return a / b;
	}
}

//Xu ly Qfloat
string processQfloat(vector<string> input) {
	//Neu la chuyen doi co so
	if (input.size() == 3) {
		int base1 = stoi(input[0]);
		Qfloat temp;
		Qfloat::ScanQfloat(temp, input[2], base1);
		if (input[1] == "-") {
			Qfloat zero;
			return Qfloat::PrintQfloat(zero - temp, base1);
		}
		int base2 = stoi(input[1]);
		return Qfloat::PrintQfloat(temp, base2);
	}
	//Neu thuc hien phep tinh
	if (input.size() == 4) {
		int base = stoi(input[0]);
		Qfloat a, b;
		Qfloat::ScanQfloat(a, input[1], base);
		Qfloat::ScanQfloat(b, input[3], base);
		return Qfloat::PrintQfloat(calcQfloat(a, b, input[2][0]), base);
	}
}

//Chia chuoi input thanh cac chuoi cach nhau boi dau cach ' '
vector<string> split(string input) {
	vector<string> result;
	int start = 0;
	while (start < input.length()) {
		int end = start;
		while (end < input.length() && input[end] != ' ')
			end++;
		result.push_back(input.substr(start, end - start));
		start = end + 1;
	}
	return result;
}

string process(string input, int mode) {
	vector<string> v_inp = split(input);
	if (mode == 1)
		return processQInt(v_inp);
	else
		return processQfloat(v_inp);
}

int main(int argc, char* argv[]) {
	//Kiem tra so luong tham so
	if (argc != 4) {
		Game calculator;
		calculator.start();
		return 0;
	}
	//Kiem tra type
	string type(argv[3]);
	int mode = 1;
	if (type == "2")
		mode = 2;
	else if (type != "1") {
		cout << type << " is not type";
		return 0;
	}
	//Mo file input
	ifstream in;
	in.open(argv[1]);
	if (in.fail()) {
		cout << "Can't open " << argv[1] << endl;
		return 0;
	}
	//Mo file output
	ofstream out;
	out.open(argv[2]);
	string input;
	//Doc file va xu ly
	while (getline(in, input))
		cout << process(input, mode) << endl;
	in.close();
	out.close();
}