#include "Gramatica.h"

Gramatica::Gramatica(string estado_inicial, vector<Produccion> producciones, Produccion dummy, set<string> terminales, set<string> noterminales)
{
	this->estado_inicial = estado_inicial;
	this->producciones = producciones;
	this->dummy = dummy;
	this->terminales = terminales;
	this->noterminales = noterminales;
}

void Gramatica::print()
{
	cout << "estado_inicial: " << this->estado_inicial << endl;
	cout << "Terminales: " << endl;
	for (string test : terminales) 
	{
		cout << test << ", ";
	}
	cout << endl;
	cout << "No Terminales" << endl;
	for (string test : noterminales)
	{
		cout << test << ", ";
	}
	cout << endl;
	cout << "Producciones" << endl;
	for (Produccion test : producciones)
	{
		test.print_Produccion();
	}
	cout << endl;
}