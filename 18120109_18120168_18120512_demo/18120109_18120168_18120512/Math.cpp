#include "stdafx.h"
#include "Math.h"
#include <iostream>
#include <sstream>
#include <iomanip>

Math::Math()
{
	//Khoi tao nhung ket hop toan tu khong hop le de kiem tra
	this->oper[0] = "/";
	this->oper[1] = "x";
	this->oper[2] = "-";
	this->oper[3] = "+";
	this->oper[4] = ".";

	int operSize = sizeof(oper) / sizeof(std::string); //Kich co cua cac toan tu

	for (int i = 0; i < operSize; i++)
	{
		for (int j = 0; j < operSize; j++)
		{
			this->invalidOper.push_back(oper[i] + oper[j]);
		}
	}


}

//Xu ly bieu thuc chuoi va tra ve ket qua cho chuoi do
std::string Math::doMath(std::string toProcess)
{
	std::string answer = toProcess;

	//Kiem tra tinh hop le cua chuoi bieu thuc
	answer = this->validate(answer);

	//Tinh toan khi chuoi bieu thuc hop le
	if (answer != "ERROR")
	{
		answer = this->calculate(answer);
	}

	return answer;
}


//Kiem tra bieu thuc chuoi hop le
std::string Math::validate(std::string toProcess)
{
	//Luu ket qua
	std::string answer = toProcess;

	/*
		Kiem tra tinh hop le cua bieu thuc
		1) Khong co 2 toan tu lien ke nhau
		2) Khong bat dau bang toan tu
		3) Khong ket thuc boi 1 toan tu	
	*/

	//Chia chuoi bieu thuc ra thanh 2 ky tu lien tiep cua chuoi
	//Vaf luu moi cap trong moi cap vector
	//So sanh moi cap voi cac ket hop toan tu khong hop le

	std::vector<std::string> pairs;
	bool isOver = false;
	int pos = 0; //Vi tri bat dau
	while (!isOver)
	{
		if (pos + 1 <= toProcess.length())
		{
			pairs.push_back(toProcess.substr(pos,2));
			pos += 1; //Chay ket cap tiep theo
		}
		else
		{
			isOver = true; //Ket thuc vong lap
		}
	}

	//Kiem tra 2 toan khong lien ke nhau
	//So sanh tung cap voi cac ket hop toan tu khong hop le
	for (int i = 0; i < pairs.size(); i++)
	{
		for (int j = 0; j < this->invalidOper.size(); j++)
		{
			if (pairs[i] == this->invalidOper[j])
			{
				answer = "ERROR";
			}
		}
	}

	if (toProcess.length() >= 1)
	{

		//Kiem tra phan tu dau hoac cuoi khong la toan tu
		for (int i = 0; i < sizeof(this->oper) / sizeof(std::string); i++)
		{
			if (toProcess.substr(0, 1) == this->oper[i] ||
				toProcess.substr(toProcess.length() - 1, 1) == this->oper[i])
			{
				answer = "ERROR";
			}
		}
	}
	return answer;
}

//Thuc hien tinh toan khi bieu thuc chuoi hop le
std::string Math::calculate(std::string toProcess)
{
	std::string holder = toProcess; //Saving the OG Answer
	holder += "F";			//Them ky hieu "F" la ket thuc bieu thuc

	//Cac toan tu co the co cua bieu thuc
	char possibleOper[] = { '+','-', '*', '/', '&', '|', '^', '~','F' };

	//Giu cac so hang cua chuoi
	std::vector<std::string> nums;
	
	//Giu cac toan tu cua chuoi
	std::vector<std::string> operators;

	int lastPos = 0; //Vi tri bat dau cua so hang cuoi cung cua chuoi

	//Lay ra so hang va toan tu
	for (int i = 0; i < holder.length(); i++)
	{
		//Checking Every Element in the String to see if its an Operator 
		for (int j = 0; j < sizeof(possibleOper) / sizeof(char); j++)
		{
			if (holder[i] == possibleOper[j])
			{
				//Tim thay so hang
				nums.push_back(toProcess.substr(lastPos, i - lastPos));

				//Tim thay toan tu 
				operators.push_back(std::string(1,possibleOper[j]));
				lastPos = i + 1;
			}
		}
	}

	//Go ky hieu "F" cuoi cung
	operators.erase(operators.begin() + operators.size() - 1);

	//Tinh toan
	double answer = std::stod(nums[0]);//Holds the Answer in a double format 

	for (int i = 0; i < operators.size(); i++)
	{
		if (operators[i] == "+")
		{
			answer += std::stod(nums[i + 1]);
		}
		else if (operators[i] == "-")
		{
			answer -= std::stod(nums[i + 1]);
		}
		else if (operators[i] == "x")
		{
			answer *= std::stod(nums[i + 1]);
		}
		else if (operators[i] == "/")
		{
			answer /= std::stod(nums[i + 1]);
		}
	}
	
	std::stringstream s;

	s << std::setprecision(6) << answer;


	return s.str(); 
}