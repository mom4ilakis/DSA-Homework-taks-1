#pragma once
#include "Student.h" 
#include <fstream>

class Konga
{
	//
	struct Node
	{
		Student st;

		Node* prev_node;
		Node* next_node;

		Node(const Student& s, Node* pnode = nullptr, Node* nnode = nullptr);
	};
public:
	class iterator
	{
		friend class Konga;
	
	private:
		Node* node_ptr;

	public:
		typedef iterator self_type;
		typedef Student value_type;
		typedef Student& reference;
		typedef Student* pointer;
		typedef std::bidirectional_iterator_tag iterator_category;
		typedef ptrdiff_t difference_type;

		iterator(Node* n);

		reference operator*();
		const reference operator*()const;
		pointer operator->();

		bool operator==(const self_type& other);
		bool operator!=(const self_type& other);

		explicit operator bool() const;

		self_type operator++();
		self_type operator--();

		self_type operator++(int);
		self_type operator--(int);
	};

public:
	//lifecycle, need for big4 because handling dynamic memory
	Konga();
	//creates a konga line with one student in it
	Konga(const Student& st);
	//loads konga line from a txt file, student are stored as follows name uni , one student per line 
	Konga(const std::string& FILENAME);

	Konga(const Konga& src);
	Konga& operator=(const Konga& src);
	~Konga();
	
	const Student& front() const;
	const Student& back()const;
	
	Student& front();
	Student& back();

	void pop_front();
	void pop_back();
	
	//prints in format student0 - student1 ...
	void print()const;

	//iteration
	iterator begin();
	iterator end();
	iterator begin() const;
	iterator end() const;

	//merges src with this konga, only if src.front is compatible with this.back;
	void merge(Konga& src);

	//finds box with student with name, else returnst nullptr
	Node* find(const std::string& name);

	Konga remove(const std::string& name);

	bool push_front(const Student& st);
	bool push_back(const Student& st);

	bool empthy()const;

	void loadFromFile(const std::string& FILENAME);
	//saves to a file in format name, uni, one student per line
	void saveToFile(const std::string& FILENAME);

private:
	//splits the list, start_ptr is the front of the new list
	Konga split(Node* start_ptr);

	void clear();
	
	void fixDummy();
	
	void copy(const Konga& oth);
private:
	Node* front_ptr;
	Node* back_ptr;
	Node* dummy_ptr;
	unsigned curSize;
};

