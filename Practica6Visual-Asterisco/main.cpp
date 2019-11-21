//Cuba Lajo Ruben Adrian
//Flores Pari Fabrizio Rodrigo
#include <iostream>
#include <string>
#include <vector>

#include "Grammar.h"
#include "Compiler.h"

using namespace std;

int main()
{
	Grammar G = getgram();
	G.print_grammar();

	Compiler compilador(G);
	string entrada;
	//cout << endl;
	cout << "Ingrese el texto a reconocer: " << endl;
	//cin.ignore();

	getline(cin, entrada);

	system("cls");
	
	bool val = compilador.Validar(remove_Spaces(entrada));
	cout << endl;
	
	cout << "RESULTADO de analizar - " << entrada << " - : ";
	if (val)
	{
		cout << "Valido" << endl;
	}
	else
	{
		cout << "Invalido" << endl;
	}
	cout << endl;
	cout << "Table: " << endl;
	compilador.tabla.print_table();
	return 0;
}
