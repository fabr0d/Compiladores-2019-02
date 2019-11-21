#include "getGram.h"

vector<string> getLines(int lines)
{
	vector<string> GramLines;
	cout << "Introdusca linea por linea" << endl;
	for (int i = 0; i < lines; i++)
	{
		string test;
		cin.ignore();
		getline(cin, test);
		GramLines.push_back(test);
	}
	cout << lines << endl;
	return GramLines;
}

Gramatica getGram(vector<string> lines)
{
	string _estado_inicial;						//1
	_estado_inicial.clear();
	vector<Produccion> _producciones;			//2
	for (size_t i = 0; i < lines.size(); i++)
	{
		if (lines[i].empty())
		{
			continue;
		}

		string _izq;
		vector<tokenContext> _der;

		stringstream ss(lines[i]);
		ss >> _izq;
		string tr; 
		ss >> tr;

		while (ss)
		{
			string st; 
			ss >> st;
			if (!st.empty())
			{
				_der.emplace_back(st);
			}
		}

		Produccion _prod(_izq, _der);

		if (_estado_inicial.empty())
		{
			_estado_inicial = _prod.izq;
		}
		_producciones.push_back(_prod);
	}

	set<string> _terminales;				//3
	for (Produccion p : _producciones)
	{
		for (tokenContext s : p.der)
		{
			if (s.isTerminal)
			{
				_terminales.insert(s.text);
			}
		}
	}

	set<string> _noterminales;				//4
	for (Produccion p : _producciones)
	{
		_noterminales.insert(p.izq);
	}

	vector<tokenContext> der1;
	der1.push_back(_producciones[0].izq);
	Produccion _dummy("S", der1);			//5

	Gramatica Grama(_estado_inicial, _producciones, _dummy, _terminales, _noterminales);
	return Grama;
}