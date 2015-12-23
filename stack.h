#pragma once

template <class type> class stack
{
private:
	type * mem;
	int size;
	int last;
public:
	stack(int _size = 0) {
		size = _size;
		last = 0;
		mem = new type[size];
	}
	stack(stack<type> const & tmp) {
		size = tmp.last;
		last = tmp.last;
		mem = new type[size];
		for (size_t i = 0; i < last; i++)
			mem[i] = tmp.mem[i];
	}
	stack<type> & operator= (stack<type> const & tmp)
 {
		if (size != tmp.size) {
			delete[] mem;
			size = tmp.size;
			mem = new type[size];
		}
		last = tmp.last;
		for (size_t i = 0; i < last; i++)
			mem[i] = tmp.mem[i];
		return *this;
	}
	void Push(type tmp) { if (last < size) mem[last++] = tmp; }//добавить элемент
	type Pop() { if (last != 0) return mem[--last]; return 0; }//взять сверху
	type Top() { if (last != 0) return mem[last - 1]; return 0; }//посмотреть последний элемент
	bool is_empty() { return(last == 0); }//проверка пустоты
	bool is_full() { return(last == size); }//проверка полноты

	int getlast() { return last; }
	int getsize() { return size; }
	~stack() { delete[] mem; }
};

