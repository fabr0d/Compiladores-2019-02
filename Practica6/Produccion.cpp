#include "Produccion.h"

Produccion::Produccion(string _izq, vector<tokenContext> _der)
{
	izq = _izq;
	der = _der;
	haveTerminals = der[0].isTerminal;
}

void Produccion::print_Produccion()
{
	cout << "Izq: " << izq << "-> Der[";
	for (tokenContext test : der)
	{
		cout << test.text << " ";
	}
	cout << "]" << endl;
	cout << "HaveTerminals?: " << haveTerminals << endl;
}