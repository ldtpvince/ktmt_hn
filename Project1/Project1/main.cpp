#include <iostream>
#include <sstream>
#include "Qfloat.h"
#include "QInt.h"

using namespace std;

int main(){
	string str("2D");
	str = strHexToBin(str);
	QInt x = 10;
	str = x.QIntToStrDec();
	return 0;
}	