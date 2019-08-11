#include "Konga.h"
#include <iostream>


Konga::Konga():front_ptr(nullptr),back_ptr(nullptr),curSize(0)
{
	dummy_ptr = new Node(Student());
}

Konga::Konga(const Student & st):front_ptr(nullptr),back_ptr(nullptr),curSize(0)
{
	dummy_ptr = new Node(Student());
	push_back(st);

}

Konga::Konga(const std::string & FILENAME):front_ptr(nullptr),back_ptr(nullptr),curSize(0)
{
	
	dummy_ptr = new Node(Student());

	loadFromFile(FILENAME);

}

Konga::Konga(const Konga & src):front_ptr(nullptr),back_ptr(nullptr),curSize(0)
{
	dummy_ptr = new Node(Student());
	
	copy(src);
}

Konga & Konga::operator=(const Konga & src)
{
	if (this != &src)
	{
		clear();

		dummy_ptr = new Node(Student());

		copy(src);
	}

	return (*this);
}


Konga::~Konga()
{
	clear();
}

const Student & Konga::front() const
{
	if (empthy())
		throw std::logic_error("List is empthy\n");
		
	
	return front_ptr->st;
}

const Student & Konga::back() const
{
	if (empthy())
		throw std::logic_error("List is empthy\n");
	
		return back_ptr->st;
}

Student & Konga::front()
{
	if (empthy())
		throw std::logic_error("List is empthy\n");


	return front_ptr->st;
}

Student & Konga::back()
{
	if (empthy())
		throw std::logic_error("List is empthy\n");


	return back_ptr->st;
}
void Konga::pop_front()
{
	if (empthy())
		throw std::logic_error("List is empthy\n");

	if (curSize == 1)
	{
		clear();

		return;
	}


	Node* dest = front_ptr;


	front_ptr = front_ptr->next_node;
	
	delete dest;
	
	front_ptr->prev_node = nullptr;

	
	curSize--;
}
void Konga::pop_back()
{
	if (empthy())
		throw std::logic_error("List is empthy\n");

	if (curSize == 1)
	{
		clear();
		return;
	}

	Node* dest = back_ptr;
	
	back_ptr = back_ptr->prev_node;
	
	delete dest;

	fixDummy();

	curSize--;

}
void Konga::print() const
{
	iterator it = begin();

	while (it!=end())
	{	
		it->print();
			
		if (it.node_ptr->next_node != dummy_ptr)
			std::cout << " - ";
		
		++it;
	}
}
Konga::iterator Konga::begin()
{
	return (front_ptr) ? iterator(front_ptr) : iterator(dummy_ptr);
}
Konga::iterator Konga::end()
{
	return iterator(dummy_ptr);
}

Konga::iterator Konga::begin() const
{
	return iterator(front_ptr);
}
Konga::iterator Konga::end() const
{
	return iterator(dummy_ptr);
}
void Konga::merge(Konga & src)
{
	if (src.front().compatible(back_ptr->st))
	{
		//because we are merging we need to empthy the src list
		while (!src.empthy())
		{
			push_back(src.front());
			src.pop_front();
		}
	}
	else
		std::cout << "Incompatible people\n";




}
Konga::Node* Konga::find(const std::string & name)
{
	Node * tmp = front_ptr;

	while (tmp != dummy_ptr)
	{
		if (tmp->st.GetName() == name)
			return tmp;
		tmp = tmp->next_node;
	}

	return nullptr;

}
Konga Konga::remove(const std::string & name)
{
	Node* tmp = find(name);
	
	//will be used if we need to split the konga, new konga will be saved in k, else k will be empthy
	Konga k;
	
	if (tmp == nullptr)
	{
		std::cout << "No student with name:" << name;
		return k;
	}

	if (tmp == front_ptr)
	{
		pop_front();
		return k;
	}
	if (tmp == back_ptr)
	{
		pop_back();
		return k;
	}
	if (tmp != nullptr)
	{
		k = split(tmp);
	}



	return k;

}
Konga Konga::split(Node* start_ptr)
{
	//used to destroy nodes, after copying them in k
	Node* tmp;
	
	Konga k;

	if (start_ptr!=nullptr)
	{
		back_ptr = start_ptr->prev_node;
		while (start_ptr != dummy_ptr)
		{
			tmp = start_ptr;
			//adding the current node to the new konga
			k.push_back(start_ptr->st);
			//next node to be copied
			start_ptr = start_ptr->next_node;
			//deleting the copied node
			delete tmp;
			
			curSize--;
		}
		k.pop_front();
		
		fixDummy();
	}
		return k;
}
bool Konga::push_front(const Student & st)
{
	if (empthy())
	{
		front_ptr = new Node(st);
		
		back_ptr = front_ptr;
		
		curSize++;
		
		fixDummy();

		return true;
	}


	if (front_ptr->st.compatible(st))
	{
		front_ptr->prev_node = new Node(st,nullptr,front_ptr);
		
		front_ptr = front_ptr->prev_node;
		
		fixDummy();
		
		curSize++;
		
		return true;
	}
	return false;
}
bool Konga::push_back(const Student & st)
{
	if (empthy())
	{
		return push_front(st); 
		return true;
	}

	if (st.compatible(back_ptr->st))
	{
		back_ptr->next_node = new Node(st, back_ptr);
		
		back_ptr = back_ptr->next_node;
		
		fixDummy();
		
		curSize++;

		return true;
	}

	return false;
}
bool Konga::empthy() const
{
	return curSize == 0;
}

void Konga::loadFromFile(const std::string & FILENAME)
{
	std::ifstream inputFile(FILENAME);

	if (inputFile.is_open())
	{
		std::string name, uni;
		

		inputFile >> name >> uni;

		while (!inputFile.eof())
		{

			if (!push_back(Student(name, uni)))
			{
				inputFile.close();

				throw std::logic_error("Incompatible students\n");
			}

			inputFile >> name;
			
			inputFile >> uni;
		}

		inputFile.close();
	}
}
void Konga::saveToFile(const std::string & FILENAME)
{
	std::ofstream outFile(FILENAME);

	if (outFile.is_open())
	{
		iterator it = begin();

		while (it != end())
		{
			outFile<<it->GetName() <<" "<<it->GetUni()<<'\n';
			++it;
		}


		outFile.close();
	}
}
void Konga::clear()
{
	Node* destroyer;
	while (front_ptr != nullptr && front_ptr != dummy_ptr)
	{
		destroyer = front_ptr;

		front_ptr= front_ptr->next_node;

		delete destroyer;

	}
	front_ptr = nullptr;
	back_ptr = nullptr;
	dummy_ptr = nullptr;
	curSize = 0;
}

void Konga::fixDummy()
{
	dummy_ptr->prev_node = back_ptr;

	if (back_ptr)
		back_ptr->next_node = dummy_ptr;
}

void Konga::copy(const Konga & oth)
{
	if (!oth.empthy())
	{
	iterator src = oth.begin();
	
	while (src != oth.end())
	{
		push_back(*src);
		++src;
	}
	}
}

Konga::Node::Node(const Student & s, Node * pnode, Node * nnode):st(s), prev_node(pnode),next_node(nnode)
{
}

Konga::iterator::iterator(Node * n) : node_ptr(n)
{
	;
}

Konga::iterator::reference Konga::iterator::operator*()
{
	return node_ptr->st;
}

const Konga::iterator::reference Konga::iterator::operator*() const
{
	return node_ptr->st;
}

Konga::iterator::pointer Konga::iterator::operator->()
{
	return &node_ptr->st;
}

bool Konga::iterator::operator==(const self_type & other)
{
	return node_ptr == other.node_ptr;
}

bool Konga::iterator::operator!=(const self_type & other)
{
	return !(*this == other);
}

Konga::iterator::self_type Konga::iterator::operator++()
{
	node_ptr = node_ptr->next_node;

	return node_ptr;
}

Konga::iterator::self_type Konga::iterator::operator--()
{
	node_ptr = node_ptr->prev_node;

	return node_ptr;
}

Konga::iterator::self_type Konga::iterator::operator++(int)
{
	iterator tmp(*this);
	
	++(*this);
	
	return tmp;
}

Konga::iterator::self_type Konga::iterator::operator--(int)
{
	iterator tmp(*this);
	--(*this);
	return tmp;
}
