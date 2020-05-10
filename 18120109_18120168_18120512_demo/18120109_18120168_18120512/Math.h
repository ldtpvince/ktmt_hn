#pragma once
#include <string>
#include <vector>

/*
	Thuc hien tinh toan
*/

class Math
{
public:
	Math();

	//Xu li bieu thuc chuoi va tra ve ket qua cua no
	std::string doMath(std::string toProcess);

	//Xac dinh tinh dung sai cua du lieu
	std::string validate(std::string toProcess);

	//Tinh toan ket qua khi du lieu da hop le
	std::string calculate(std::string toProcess);

	private:

		//Moi phan tu giu chuoi 2 toan tu khong hop le ket hop voi nhau
		std::vector<std::string> invalidOper; 

		std::string oper[5];
};