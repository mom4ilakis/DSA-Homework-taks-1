#include "UserInputH.h"



UserInputH::UserInputH()
{
}

int UserInputH::recCommand(const std::string & command)
{
	if (command == "append")
		return 0;
	if (command == "removeLast")
		return 1;
	if (command == "removeFirst")
		return 2;
	if (command == "remove")
		return 3;
	if (command == "merge")
		return 4;
	if (command == "print")
		return 5;
	if (command == "quit")
		return 6;




	return -1;


}

bool UserInputH::applyCommand(int ind)
{
	std::string name,uni;
	size_t index1, index2;


	switch (ind)
	{
	case 0://append
	{
		try
		{

		std::cout << "Enter name & uni and line index\n";
		std::cin >> name >> uni >> index1;
		
		if (dance.append(Student(name, uni), index1))
			std::cout << "Added student " << name << " from " << uni << "to " << index1 << '\n';
		else
			std::cout << "Incompatible people\n";
		}
		catch (std::out_of_range& e)
		{
			std::cout << e.what();
		}
	}
	break;
	case 1://removeLast
	{
		try
		{

			std::cout << "Enter  index\n";
			std::cin >> index1;
			dance.removeLast(index1);
			std::cout << "Removed last from: " << index1<<'\n';
		}
		catch (std::out_of_range& e)
		{
			std::cout << e.what();
		}
		catch (std::logic_error& e)
		{
			std::cout << e.what();
		}
	}
	break;
	case 2://removeFirst
	{
		try
		{

		std::cout << "Enter index\n";
		
		std::cin >> index1;
		
		dance.removeFirst(index1);
		
		std::cout << "Removed first from: " << index1 << '\n';
		}
		catch (std::out_of_range& e)
		{
			std::cout << e.what();
		}
		catch (std::logic_error& e)
		{
			std::cout << e.what();
		}

	}
	break;
	case 3://remove
	{
		try
		{

			std::cout << "Enter name & index\n";

			std::cin >> name >> index1;

			if (dance.remove(name, index1))
				std::cout << "A new konga line was created\n";
			else
				std::cout << "No new konga lines were created\n";


			//std::cout << "Removed " << name << " from: " << index1 << '\n';
		}
		catch (std::out_of_range& e)
		{
			std::cout << e.what();
		}

	}
	break;
	case 4://merge
	{
		try
		{

		std::cout << "Enter index1 & index2\n";
		std::cin >> index1 >> index2;

		if (dance.merge(index1, index2))
			std::cout << "Merged konga lines" << index1 << " & " << index2 << '\n';
		}
		catch (std::out_of_range& e)
		{
			std::cout << e.what();
		}
	}
	break;
	case 5://print
		dance.print();
	break;

	case 6://quit
		return false;
	default:
		std::cout << "Unknown command\n" << "Available commands:\n append<Name, Uni, lineIndex> \n removeLast<lineindex> \n removeFirst<lineIndex>\n"
			<< " remove<name,lineIndex> \n print \n quit\n";
		break;
	}




	return true;
}


UserInputH * UserInputH::GetInstance()
{
	static UserInputH UIH;

	return &UIH;
}

void UserInputH::TakeInput()
{
	int Cindx = -1;
	std::string command;

	while (applyCommand(Cindx))
	{
		std::cout << ">>";
		
		std::cin >> command;

		Cindx = recCommand(command);
	}





}

UserInputH::~UserInputH()
{
}
