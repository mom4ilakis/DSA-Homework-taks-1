#pragma once
#include "Array.h"
#include <iostream>
class UserInputH
{
public:
	static UserInputH* GetInstance();

	void TakeInput();

	~UserInputH();
private:
	UserInputH();
	int recCommand(const std::string& command);
	bool applyCommand(int ind);


private:
	Array dance;
};

