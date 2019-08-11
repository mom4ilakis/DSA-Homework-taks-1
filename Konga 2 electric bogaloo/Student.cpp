#include "Student.h"
#include <iostream>


Student::Student():name("NULL"),uni("NULL")
{
}

Student::Student(const std::string & Name, const std::string & Uni)
{

	try
	{
		SetUni(Uni);
	}
	catch (const std::invalid_argument& e)
	{
		std::cout << e.what();
		throw;
	}

	SetName(Name);

}


Student::~Student()
{
}

bool Student::compatible(const Student & st) const
{
	if (this->uni == st.uni || uni == "NULL" || st.uni == "NULL")
		return true;

	if (this->uni == "fmi")
		if ( st.uni == "tu")
			return true;

	if (this->uni == "tu")
		if (st.uni == "unss")
			return true;

	if (this->uni == "unss")
		if (st.uni == "fmi")
			return true;

	return false;
}

std::string Student::GetUni() const
{
	return uni;
}

void Student::print() const
{

	std::cout << '(' << name << ", " << uni << ')';


}

std::string Student::GetName() const
{
	return name;
}
void Student::SetName(const std::string & Name)
{
	name = Name;
}

void Student::SetUni(const std::string & Uni)
{
	if (Uni == "unss" || Uni == "fmi" || Uni == "tu")
		uni = Uni;
	else
	{

		std::string message = "University not supported: ";
		message + uni;
		message + '\n';

		throw std::invalid_argument(message);
	}


}
