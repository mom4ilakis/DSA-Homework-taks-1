#pragma once
#include <string>
class Student
{
public:
	//no need for copy ctor & operator=, since the class is not handling dynamic memory
	Student();
	Student(const std::string& Name, const std::string& Uni);
	~Student();

	//checks of this student can stand behind st
	bool compatible(const Student& st)const;
	
	
	std::string GetName()const;

	std::string GetUni()const;


	//prints the student in format (name, uni)
	void print() const;

private:
	void SetName(const std::string& Name);
	void SetUni(const std::string& Uni);


private:
	std::string name;
	std::string uni;
};

