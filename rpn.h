#pragma once
#include<iostream>
#include <string>
#include "stack.h"
#include "table.h"
class rpn {
private:
	string *stringarr;
	int size;// объем полного массива
	int count;// реальное кол-во элементов, занимаемых массив
	table<double> valuetable;
	table<int> priortable;
	stack<record<int> >  priorstack;

	void  MakePrior() {
		priortable = table<int>(10);
		priortable.Add("+", 1);
		priortable.Add("-", 1);
		priortable.Add("*", 2);
		priortable.Add("/", 2);
		priortable.Add("^", 3);
	}
	void LeftBreaket() {
		priorstack.Push(record<int>("(", 0));
	}
	void RightBreaket() {
		while (!(priorstack.is_empty()) && priorstack.Top().Getname() != "(") {
			stringarr[count++] = priorstack.Pop().Getname();
			//std::cout << priorstack.Pop().Getname() << endl;
		}
	priorstack.Pop();
	}
	void Operand(string _str) {
		stringarr[count++] = _str;
		if ((_str[0] >= '0') && ((int)(_str[0]) <= '9'))
			valuetable.Add(_str, std::stod(_str));
		else valuetable.Add(_str, 0);
	}
	void Operation(record <int> tmp) {
		int f,  g ,p,q;
		f = !priorstack.is_empty();
		g = priorstack.Top().Getvalue() >= tmp.Getvalue();
		p = priorstack.Top().Getvalue();
		q = tmp.Getvalue();
		while ( !(priorstack.is_empty()) && (priorstack.Top().Getvalue() >= tmp.Getvalue()) ) 
			stringarr[count++] = priorstack.Pop().Getname();

		priorstack.Push(tmp);
	}
	void EndString(void) {
		while (!(priorstack.is_empty()))
			stringarr[count++] = priorstack.Pop().Getname();
	}
	void To_String(string st, int &k, string *w) {
		k = 0;
		string sth = "+-*/^()";
		int len = st.length();
		int l;
		for (size_t i = 0; i < len - 1; i++)
			w[i] = "";

		for (int i = 0; i < len; i++)
		{
			l = sth.find(st[i]);
			if (l < 0)
				w[k] += st[i];
			else {
				if (w[k] != "")
					k++;
				w[k] += st[i];
				k++;
			}
		}
		if (w[k] != "")
			k++;
	}
	void LexemsToRpn(string str)
	{
		int lexsize = 0;

		string *lexems = new string[str.size() + 1];

		To_String(str, lexsize, lexems);
		count = 0;
		for (int i = 0;i < lexsize;i++)
		{
			if (lexems[i] == "(")
				LeftBreaket();
			else if (lexems[i] == ")")
				RightBreaket();
			else
			{
				int priority = priortable.Search_value(lexems[i]);
				if (priority <= 0)
				{
					Operand(lexems[i]);
					if (valuetable.Search_number(lexems[i]) < 0)
						if (lexems[i][0]<'0' || lexems[i][0]>'9')
							valuetable.Add(lexems[i], 0);
						else
							valuetable.Add(lexems[i], atoi(lexems[i].c_str()));
				}
				else
					Operation(record<int>(lexems[i],priortable.Search_value(lexems[i])));
			}
	
		}
		EndString();
		delete[] lexems;
	}
public:
	rpn(string str = "()")
	{
		valuetable = table<double>(25);
		stringarr = new string[100];
		priorstack = stack<record<int> >(20);
		size = 0;
		count = 0;
		MakePrior();
		LexemsToRpn(str);
	};
	~rpn(void) {
		delete[] stringarr; 
	}
	rpn(rpn  & tmp) {
		//delete[] stringarr;
		stringarr = new string[tmp.count];
		size = tmp.size;
		count = tmp.count;
		for (size_t i = 0; i < count; i++)
			stringarr[i] = tmp.stringarr[i];
		valuetable = tmp.valuetable;
		priorstack = tmp.priorstack;
	
	};
	rpn & operator=( rpn & tmp) {

		if (count != tmp.count)
			delete[] stringarr;

		stringarr = new string[tmp.count];
		count = tmp.count;
		for (int i = 0;i < count;i++)
			stringarr[i] = tmp.stringarr[i];
		valuetable = tmp.valuetable;
		priorstack = tmp.priorstack;
		return *this;
	};
	string * Getrpn() {
		return stringarr;
	}
	table<double> Getvaluetable() { 
		return valuetable; 
	}
	int Getsize() { return count; }



};
