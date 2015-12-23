#pragma once
#include "record.h"
template<class type> class table
{
private: record<type> * mem;
private: int size;//размер
private: int count;//сколько заполнено 
public:
	table(int _size = 0) {
		size = _size;
		count = 0;
		mem = new record<type>[size];
	};
	table(table<type> & tmp)  {
		size = tmp.size;
		count = tmp.count;
		mem = new record<type>[size];
		for (size_t i = 0; i < count; i++)
			mem[i] = tmp.mem[i];
	};
	table<type> & operator=(table<type> & tmp) {
		if (size < tmp.size) {
			delete[] mem;
			size = tmp.size;
			count = tmp.count;
			mem = new record<type>[size];
		}
		for (size_t i = 0; i < tmp.count; i++)
			mem[i] = tmp.mem[i];

		count = tmp.count;
		return *this;
	};
	void Add(record<type> tmp) {
		int l = Search_number(tmp.Getname());
		if (l == -1 && !is_full()) 
			mem[count++] = tmp;
		else 
			mem[l] = tmp;
	};
	void Add(string name, type value) {
		record<type> tmp(name, value);
		this->Add(tmp);
		/*int l = Search_number(tmp.Getname());
		if (l == -1 && !is_full()) mem[count++] = tmp;
		else mem[l] = tmp;*/
	}
	void Dell(string _name) {
		int i = Search_number(_name);
		//если упорядочен
		/*for (size_t j = i; j < count-1 ; j++)
				mem[j] = mem[j + 1];*/
		mem[i] = mem[--count];
		
	};
	type Search_value(string _name) {
		int i = Search_number(_name);
		if (i != -1)
		return mem[i].Getvalue();
		return -1;
	};
	int  Search_number(string _name) {
		int i = 0, c = count;
		while (c && mem[i].Getname() != _name){ i++;c--;}
		if (c) return (i);
		return -1;
	};
	int Getcount()  { return count; };
	bool is_empty() { return (count == 0); };
	bool is_full() { return (count == size); };
	record<type> Getrecord(int index) { return mem[index]; };
	~table() { delete[] mem; };
};

