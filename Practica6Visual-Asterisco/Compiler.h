#pragma once

#include <iostream>
#include <stack>
#include <map>
#include <vector>
#include <iomanip> 

#include "CompilerState.h"
#include "Grammar.h"
#include "Table.h"
using namespace std;

class Compiler
{
public:
	Grammar gramatica;
	string sentencia;
	Table tabla;
	map<string, string> contexto;

	Compiler(Grammar gramatica_)
	{
		gramatica = gramatica_;
	}
	bool Validar(string sentencia)
	{
		this->sentencia = sentencia;
		CompilerState dummy = CompilerState(&gramatica.dummy, 0, nullptr);
		stack<CompilerState*> chart;
		chart.push(&dummy);

		while (!chart.empty())
		{
			CompilerState* estado = chart.top();
			cout << estado->produccionRef->to_string() << endl;
			RowState row;
			row.productionRef = estado->produccionRef;
			row.posAst = estado->posAsterico;

			if (estado->fail == true)
			{
				chart.pop();
				row.state = "RECHAZADO";
				cout << "RECHAZADO" << endl;
			}

			else if (estado->posAsterico >= estado->produccionRef->der.size())
			{
				aceptar(estado, chart);
				row.state = "ACEPTADO";
				cout << "ACEPTADO" << endl;
			}

			else if (estado->produccionRef->haveTerminals)
			{
				cout << "UNIFICO" << endl;
				unificar(estado);
			}

			else if (estado->posAsterico < estado->produccionRef->der.size())
			{
				estado->fail = true;
				expande(estado, chart);
				row.state = "EXPANDIENDOSE";
				cout << "EXPANDIENDOSE" << endl;
			}

			if (!row.state.empty())
			{
				tabla.push(row);
			}
		}
		return !dummy.fail;
	};
	void imprimirTabla()
	{
		tabla.print_table();
	};

	void unificar(CompilerState* estado)
	{
		string terminal = estado->produccionRef->der[0].text;
		bool match = true;
		for (int i = 0; i < terminal.size(); ++i)
		{
			int j = i + estado->posPalabra;
			if (j > sentencia.size() || sentencia[j] != terminal[i])
			{
				match = false;
			}
		}

		CompilerState* padre = estado->origen;
		if (match)
		{
			bool conflicto = false;
			for (pair<string, string> p : estado->produccionRef->izq.context)
			{
				if (contexto.count(p.first) > 0)
				{
					if (contexto[p.first] != p.second)
					{
						conflicto = true;
					}
				}
			}
			if (!conflicto)
			{
				cout << "SIN CONFLICTO" << endl;
				estado->posAsterico++;
				estado->posPalabra += terminal.size();

				for (pair<string, string> p : estado->produccionRef->izq.context)
				{
					contexto[p.first] = p.second;
				}
			}
			else
			{
				cout << "HAY CONFLICTO" << endl; estado->fail = true;
			}
		}
		else
		{
			cout << "FALLO" << endl; estado->fail = true;
		}
	};
	void expande(CompilerState* estado, stack<CompilerState*>& chart)
	{
		vector<Produccion*> belowProd = findProductions(estado);
		for (Produccion* p : belowProd)
		{
			CompilerState* newstate = new CompilerState(p, estado->posPalabra, estado);
			chart.push(newstate);
		}
	};
	void aceptar(CompilerState* estado, stack<CompilerState*>& chart)
	{
		chart.pop();
		CompilerState* padre = estado->origen;
		if (padre != nullptr)
		{
			padre->posAsterico++;
			padre->posPalabra = estado->posPalabra;
			padre->fail = false;
		}
	};
	vector<Produccion*> findProductions(CompilerState* estado)
	{
		int posAst = estado->posAsterico;
		string symbName = estado->produccionRef->der[posAst].text;
		vector<Produccion*> producs;
		for (Produccion& p : gramatica.producciones)
		{
			if (p.izq.text == symbName)
			{
				producs.push_back(&p);
			}
		}
		return producs;
	};
};
