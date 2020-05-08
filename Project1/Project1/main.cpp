#include <iostream>
#include "Qfloat.h"
#include "QInt.h"

using namespace std;

int main(){
	Qfloat x("12.4"), y("1.2"), z;
	z = x / y;
	Qfloat::PrintQfloat(z, 10);
	return 0;
}