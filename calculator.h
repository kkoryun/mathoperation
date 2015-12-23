#pragma once
#include "rpn.h"
#include "stack.h"
class calculator
{
private:
	rpn _rpn;
	stack<double> _stack;
	table<double> valuetable;
public:
	calculator(string str=""){
	
	_rpn = rpn(str);
		_stack = stack<double>(20);
		valuetable = _rpn.Getvaluetable();
	}
	double Calculation() {
		string * s = _rpn.Getrpn();

		double Left = 0, Right = 0;
		for (int i = 0; i < _rpn.Getsize(); i++) {
			
			int l = valuetable.Search_number(s[i]);
			if (l != -1) {
				_stack.Push(valuetable.Search_value(s[i]));
			}
			else {
				Right = _stack.Pop();
				Left = _stack.Pop();
				if (s[i] == "+")
					_stack.Push(Left + Right);
				else {
					if (s[i] == "-")
						_stack.Push(Left - Right);
					else {
						if (s[i] == "*")
							_stack.Push(Left * Right);
						else {
							if (s[i] == "/")
								if (Right != 0)
									_stack.Push(Left / Right);
								else
									_stack.Push(0);
							else if (s[i] == "^")
								if (Left > 0)
									_stack.Push(exp(Right*log(Left)));
								else
									_stack.Push(0);
						}
					}
				}

			}
		}
		return _stack.Pop();
	}
	table<double> Getvaluetable(){
		return valuetable;
	}
	void Setvalue(string s, double d) {
		valuetable.Add(s, d);
	}
	string* Getrpn() {
		return _rpn.Getrpn();
	}
	int Getrpnsize() {
		return _rpn.Getsize();
	}
	};


	//////////////////////////////////////////////////////// 





	




