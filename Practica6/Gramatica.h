#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <set>
#include "Produccion.h"
using namespace std;

class Gramatica
{
public:
	string estado_inicial;
	vector<Produccion> producciones;
	Produccion dummy;
	set<string> terminales;
	set<string> noterminales;
	Gramatica() = default;
	Gramatica(
		string estado_inicial, 
		vector<Produccion> producciones, 
		Produccion dummy, 
		set<string> terminales,
		set<string> noterminales
	);
	void print();
};