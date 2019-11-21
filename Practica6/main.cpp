//Cuba Lajo Ruben Adrian
//Flores Pari Fabrizio Rodrigo
#include <iostream>
#include "tokenContext.h"
#include "Produccion.h"
#include "Gramatica.h"
#include "getGram.h"
#include "EstadoCompilador.h"
#include "Compiler.h"

using namespace std;

string removeWhiteSpaces(string str)
{
	string ans;
	for (char c : str)
		if (c != ' ')
			ans += c;
	return ans;
}

// USA CIN
string userInput()
{
	cout << "Ingrese el texto a reconocer" << endl;
	string s; getline(cin, s);
	return s;
}


int main()
{
	cout << "Numero de lineas de la Gram: "; int numLines; cin >> numLines;
	vector<string> GramLines = getLines(numLines);

	Gramatica G = getGram(GramLines);
	Compiler compilador(G);
	G.print();
	string testcase = removeWhiteSpaces(userInput());
	cout << "testcase: " << testcase << endl;
	if (compilador.esSentenciaValida(testcase))
		cout << "Sentencia valida" << endl;
	else
		cout << "Sentencia NO valida" << endl;
	return 0;
}
