#pragma once
#include "Konga.h"
class Array
{
public:
	Array();
	
	Array(const Array& src) = delete;
	Array& operator=(const Array& src) = delete;

	~Array();

	//returns true of append is successful, st is compatible with k_arr[index].back.
	//if index >= cur_size, it add a new konga line with index curr_size, changes argument index to the real index for the student
	bool append(const Student& st, size_t& index);
	
	//throws std::out_of_range if index >= cur_size
	void removeLast(size_t index);
	//throws std::out_of_range if index >= cur_size
	void removeFirst(size_t index);

	void push_back(const Konga& k);
	
	bool remove(const std::string& name, size_t index);

	//merges lines 1 & lines2 , returns true if successful, aka st from line2.front is compatible with st form line1.back
	bool merge(size_t index1, size_t index2);

	void pop_back();
	
	//prints in format lineO: stundent1 ....
	void print()const;


	Konga& back();
	
	const Konga& back()const;


	const Konga& operator[](size_t index)const;
	Konga& operator[](size_t index);

	size_t size()const;
private:
	void clear();
	void copy(const Array& source);
	void resize();
	void fixIndexes(size_t s_index);
	void addLine(size_t index);
private:
	size_t cur_size;
	size_t max_size;
	Konga* k_arr;
};

