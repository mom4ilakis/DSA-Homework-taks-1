#include "Array.h"
#include<iostream>


Array::Array():max_size(20),cur_size(1)
{
	k_arr = new Konga[max_size];
}


Array::~Array()
{
	clear();
}

bool Array::append(const Student & st, size_t& index)
{
	if (index >= cur_size)
	{
		index = cur_size;

		push_back(Konga(st));
		
		return true;
	}
	else
		return (*this)[index].push_back(st);

}

void Array::removeLast(size_t index)
{

	(*this)[index].pop_back();

	if ((*this)[index].empthy())
		fixIndexes(index);
}

void Array::removeFirst(size_t index)
{
	(*this)[index].pop_front();

	if ((*this)[index].empthy())
		fixIndexes(index);
}

void Array::push_back(const Konga & k)
{
	if (cur_size == max_size)
		resize();

	k_arr[cur_size++] = k;
}

bool Array::remove(const std::string & name, size_t index)
{

	Konga tmp = (*this)[index].remove(name);

	if ((*this)[index].empthy())
		fixIndexes(index);

	if (!tmp.empthy())
	{
		(*this).push_back(tmp);
		return true;
	}
	return false;
}

bool Array::merge(size_t index1, size_t index2)
{
	Konga *dest = &(*this)[index1];
	Konga *src = &(*this)[index2];
	
	if (src->front().compatible(dest->back()))
	{
	
		while (!src->empthy())
		{
			dest->push_back(src->front());
			src->pop_front();
		}


		fixIndexes(index2);

		return true;
	}
	else
		std::cout << "Incompatible people\n";



	return false;
}

void Array::pop_back()
{
	if (cur_size)
		cur_size--;
	else
		throw std::logic_error("Array is empthy\n");
}

void Array::print() const
{
	for (size_t i = 0; i < cur_size; ++i)
	{
		if (!k_arr[i].empthy())
		{

			std::cout << "Line" << i << ':';

			k_arr[i].print();

			std::cout << '\n';
		}
	}
}

Konga & Array::back()
{
	return (*this)[cur_size-1];
}

const Konga & Array::back() const
{
	return (*this)[cur_size - 1];
}

const Konga& Array::operator[](size_t index) const
{
	if (index >= cur_size)
		throw std::out_of_range("Index is out of range in Array\n");

	return k_arr[index];
}

Konga& Array::operator[](size_t index)
{
	return  const_cast<Konga&>(static_cast<const Array&>(*this)[index]);
}

size_t Array::size() const
{
	return cur_size;
}

void Array::clear()
{
	delete[] k_arr;
	k_arr = nullptr;
	cur_size = 0;
	max_size = 0;
}

void Array::copy(const Array& source)
{
	k_arr = new Konga[source.max_size];

	for (size_t i = 0; i < source.cur_size; ++i)
	{
		k_arr[i] = source[i];
	}
	cur_size = source.cur_size;
	max_size = source.max_size;
}

void Array::resize()
{

	size_t new_size = max_size * 2;

	Konga* tmp = new Konga[new_size];

		for (size_t i = 0; i < cur_size; ++i)
		{
			tmp[i] = k_arr[i];
		}

		delete[] k_arr;

		k_arr = tmp;

		max_size = new_size;
}

void Array::fixIndexes(size_t s_index)
{
	if (s_index > cur_size)
		throw std::out_of_range("s_index is out of range in Array\n");

	for (size_t i = s_index; i < cur_size-1; ++i)
	{
		k_arr[i] = k_arr[i + 1];
	}
	cur_size--;
}

void Array::addLine(size_t index)
{
	if (index >= cur_size)
	{
		Konga empt;
		
		size_t tmpInd = cur_size;

		while (index > max_size)
			resize();

		for (size_t i = cur_size; i <= index; ++i)
		{
			k_arr[i] = empt;
			tmpInd++;
		}
		
		cur_size = tmpInd;
	}

}

