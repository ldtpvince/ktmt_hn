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
	std::string doMath(std::string toProcess, int mode);

	//Ham su dung de chuyen he tu mode1 sang mode2
	std::string changeNumeral(std::string toProcess, int mode1, int mode2);
	private:

		//Moi phan tu giu chuoi 2 toan tu khong hop le ket hop voi nhau
		std::vector<std::string> invalidOper; 

		std::string oper[5];
};