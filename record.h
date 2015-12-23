#pragma once
#include <string>
using namespace std;
template <class type>  class record
{
private:
	string name;
	type value;
public:
	record(string _name = "", type _value = 0) {
		name = _name;
		value = _value;
	};

	string Getname()  const { return name;   }
	type   Getvalue() const { return value;  }
	void   SetValue(type _value) { value = _value; }
	friend ostream& operator<< (ostream & out, record & _outstream) {
		out << _outstream.name << " " << _outstream.value;
		return out;
	}

};

