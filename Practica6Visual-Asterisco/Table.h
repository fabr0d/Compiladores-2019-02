#pragma once
#include "CompilerState.h"

struct RowState
{
	Produccion* productionRef;
	string state;
	int posAst;
};

class Table
{
private:
	vector<RowState> table;

public:
	void push(RowState row)
	{
		table.push_back(row);
	}

	void print_table()
	{
		for (RowState row : table)
		{
			cout << row.state << " || " << getProdWithAst(row) << endl;
		}
	}

	string getProdWithAst(RowState row)
	{
		Produccion* prod = row.productionRef;
		string str = prod->izq.to_string() + "->{";
		int i = 0;
		for (; i < prod->der.size(); ++i)
		{
			Symbol symb = prod->der[i];
			if (i == row.posAst)
			{
				str += "*";
			}
			str += symb.to_string() + " ";
		}
		str.erase(str.end() - 1);
		if (i == row.posAst)
		{
			str += "*";
		}
		str += "}";
		return str;
	}
};