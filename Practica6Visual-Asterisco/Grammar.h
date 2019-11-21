#pragma once

#include <iostream>
#include <stack>
#include <map>
#include <vector>
#include <iomanip>
#include <set>
#include <fstream>
#include <sstream>
#include <string>

#include "Production.h"

using namespace std;

class Grammar
{
public:
	string estado_inicial;
	vector<Produccion> producciones;
	Produccion dummy;
	set<string> terminales;
	set<string> noterminales;

	Grammar() = default;

	Grammar(string estado_inicial, vector<Produccion> producciones, Produccion dummy, set<string> terminales, set<string> noterminales)
	{
		this->estado_inicial = estado_inicial;
		this->producciones = producciones;
		this->dummy = dummy;
		this->terminales = terminales;
		this->noterminales = noterminales;
	}


	void print_grammar()
	{
		cout << "estado_inicial = " << this->estado_inicial << endl << endl;

		cout << "Terminales" << endl;
		for (string s : terminales)
		{
			cout << s << ", ";
		}
		cout << endl;

		cout << "No Terminales" << endl;
		for (string s : noterminales)
		{
			cout << s << ", ";
		}
		cout << endl;

		cout << "Producciones" << endl;
		for (Produccion p : producciones)
		{
			cout << p << endl;
		}
	}
};


Grammar getgram()
{
	cout << "Ingrese el numero de lineas de la gramatica: ";
	int lines;
	cin >> lines;
	cout << "Ingrese un por una las lineas de la gram" << endl;
	vector<string> grammarLines;

	string estado_inicial;
	vector<Produccion> producciones;
	set<string> terminales;
	set<string> noterminales;
	cout << endl;
	cin.ignore();
	for (size_t i = 0; i < lines; i++)
	{
		string tempo;
		getline(cin, tempo);
		grammarLines.push_back(tempo);
	}

	//Producciones
	for (size_t i = 0; i < grammarLines.size(); i++)
	{
		if (grammarLines[i].empty())
		{
			continue;
		}

		stringstream ss(grammarLines[i]);
		string s;
		Symbol izq;
		ss >> s;
		izq.build(s);
		string trash;
		ss >> trash;
		vector<Symbol> der;
		while (ss >> s)
		{
			if (!s.empty())
			{
				Symbol d;
				d.build(s);
				der.push_back(d);
			}
		};
		Produccion prod = Produccion(izq, der);

		if (estado_inicial.empty())
		{
			estado_inicial = prod.izq.text;
		}
		producciones.push_back(prod);
	}

	//Terminales
	for (Produccion p : producciones)
	{
		for (Symbol s : p.der)
		{
			if (s.isTerminal)
			{
				terminales.insert(s.text);
			}
		}
	}

	//NoTerminales
	for (Produccion p : producciones)
	{
		noterminales.insert(p.izq.text);
	}

	//Dummy
	Symbol izq;
	izq.build(producciones[0].izq.to_string());
	izq.text = "S";

	vector<Symbol> der;
	der.push_back(producciones[0].izq);
	Produccion dummy(izq, der);
	
	Grammar G(estado_inicial, producciones, dummy, terminales, noterminales);
	return G;
}

string remove_Spaces(string str)
{
	string ans;
	for (char c : str)
		if (c != ' ')
			ans += c;
	return ans;
}