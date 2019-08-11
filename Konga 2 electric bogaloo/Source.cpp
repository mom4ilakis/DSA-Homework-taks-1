#include "Student.h"
#include <iostream>
#include "Konga.h"
#include "Array.h"
#include "UserInputH.h"


int main()
{

	UserInputH * uihp = UserInputH::GetInstance();


	uihp->TakeInput();



	return 0;
}