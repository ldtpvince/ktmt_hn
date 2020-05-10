#include <iostream>
#include "Qfloat.h"
#include "QInt.h"

using namespace std;

int main(){
	QInt x;
	x = BinToDec("1010");
	PrintQInt(cout, x, 10);
	return 0;
}	