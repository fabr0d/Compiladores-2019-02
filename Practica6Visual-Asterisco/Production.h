#pragma once
#include "Symbol.h"
#include <vector>

class Produccion
{
public:
	Symbol izq;
	vector<Symbol> der;
	bool haveTerminals;

	Produccion() = default;

	Produccion(Symbol izq, vector<Symbol> der) : izq(izq), der(der)
	{
		haveTerminals = der[0].isTerminal;
	}

	string to_string() const
	{
		string s = izq.to_string() + "->{";
		for (Symbol symb : der)
		{
			s += symb.to_string() + " ";
		}
		s.erase(s.end() - 1);
		s += "}";
		return s;
	}
};

ostream& operator<<(ostream& o, const Produccion& prod)
{
	return o << prod.to_string();
}