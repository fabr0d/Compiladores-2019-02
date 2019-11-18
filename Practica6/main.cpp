//Cuba Lajo Ruben Adrian
//Flores Pari Fabrizio Rodrigo
#include <set>
#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <sstream> 
#include <string>
#include <map>
#include <queue>
#include <stack>

#include "tokenContext.h"
#include "Produccion.h"
#include "Gramatica.h"

using namespace std;

//reemplazar el builder por mi propia funcion esta tendrea que 
//retornar una gramatica mediante una funcion
//la gramatica tendra: string estado inicial, vector<Produccion> producciones, getDummy(), set<string>terminales, set<string> no terminales

Gramatica getGram(vector<string> grammar)
{
	Gramatica rpta;

	string str1(":=");
	for (int i = 0; i < grammar.size(); i++)
	{
		size_t found = grammar[i].find(str1);
		string derecha = grammar[i].substr(found + 2, grammar[i].size() - 1);
		string izquierda = grammar[i].substr(0, found - 1);

		//parte izquierda (no terminales)
		izquierda.erase(remove_if(izquierda.begin(), izquierda.end(), ::isspace), izquierda.end());

		//parte derecha(entre terminales y no terminales) verificar por |
		string derechatemporal = derecha;

		vector<string> derecha_list;
		istringstream iss(derecha);
		for (string derecha; iss >> derecha; )
		{
			derecha_list.push_back(derecha);
		}

		//verificar si hay operador "|"
		vector<vector<tokenContext>> derechas_por_o;
		vector<tokenContext> temporal;//string temporal
		while (derecha_list.size() > 0)
		{
			if (derecha_list[0] == "|")
			{
				derecha_list.erase(derecha_list.begin());//borra el primero
				derechas_por_o.push_back(temporal);
				temporal.clear();
			}
			else
			{
				temporal.push_back(derecha_list[0]);
				derecha_list.erase(derecha_list.begin());
				if (derecha_list.size() == 0)
				{
					derechas_por_o.push_back(temporal);
					temporal.clear();
				}
			}
		}
		for (int i = 0; i < derechas_por_o.size(); i++)
		{
			Produccion p1;
			p1.izq = izquierda;
			p1.der = derechas_por_o[i];
			//send produccion to grammar
			rpta.production.push_back(p1);
		}
	}

	set<string>terminalesrtpa;
	set<string>noterminalesrtpa;
	//verificar cuales son terminales o no terminales
	for (int i = 0; i < rpta.production.size(); i++)
	{
		terminalesrtpa.insert(rpta.production[i].izq);
	}
	rpta.terminales = terminalesrtpa;
	for (int i = 0; i < rpta.production.size(); i++)
	{
		for (int j = 0; j < rpta.production[i].der.size(); j++)
		{
			//Si no hay ocurrencias en mi set de terminales de la produccion de la derecha
			if (rpta.terminales.count(rpta.production[i].der[j]) == 0)
			{
				//lo meto en el set de no terminales
				rpta.noterminales.insert(rpta.production[i].der[j]);
			}
		}
	}

	return rpta;
}

class BuilderGramatica
{
private:
	string estado_inicial;
	vector<Produccion> producciones;
	set<string> terminales;
	set<string> noterminales;

public:
	Gramatica buildGramatica(string filename)
	{
		clearAtributes();
		// Producciones
		setProducciones(filename);
		setTerminales();
		setNoTerminales();
		Gramatica G(estado_inicial, producciones, getDummy(), terminales, noterminales);
		return G;
	}

	void setProducciones(string filename)
	{
		ifstream file = getIfstream(filename);
		string line;
		while (getline(file, line))
		{
			if (line.empty()) continue;
			Produccion prod = parserProduccion(line);
			if (estado_inicial.empty()) estado_inicial = prod.izq;
			producciones.push_back(prod);
		}
	}

	void setTerminales()
	{
		for (Produccion p : producciones)
			for (tokenContext s : p.der)
				if (s.isTerminal)
					terminales.insert(s.text);
	}

	void setNoTerminales()
	{
		for (Produccion p : producciones)
			noterminales.insert(p.izq);
	}

	Produccion getDummy()
	{
		vector<tokenContext> der;
		der.push_back(producciones[0].izq);
		return Produccion("S", der);
	}

	Produccion parserProduccion(string line)
	{
		string izq;
		vector<tokenContext> der;
		stringstream ss(line);
		ss >> izq;
		string trash; ss >> trash;
		while (ss)
		{
			string s; ss >> s;
			if (!s.empty())
				der.emplace_back(s);
		}
		return Produccion(izq, der);
	}

	ifstream getIfstream(string filename)
	{
		ifstream file(filename.c_str());
		if (!file)
		{
			cout << "No existe archivo " << filename << endl;
			exit(EXIT_FAILURE);
		}
		return file;
	}

	void clearAtributes()
	{
		estado_inicial.clear();
		producciones.clear();
		terminales.clear();
		noterminales.clear();
	}
};

enum tipoNodo { NODO_AND, NODO_OR };

struct EstadoCompilador
{
	Produccion* produccionRef;
	int posAsterico;
	int posPalabra;
	EstadoCompilador* origen;
	int tipo;
	bool fail;  // false en AND, true en OR
	// Nodos tipo AND cuando falla un hijo, este falla
	// Nodos tipo OR cuando falla un hijo, sigue al siguiente hijo, hasta que todos fallen
};


class Compilador
{
private:
	Gramatica gramatica;
	string sentencia;
public:

	Compilador(Gramatica gramatica) : gramatica(gramatica)
	{}

	bool esSentenciaValida(string sentencia)
	{
		this->sentencia = sentencia;
		EstadoCompilador dummy{ &gramatica.dummy, 0, 0, nullptr, NODO_AND, false };
		stack<EstadoCompilador*> chart;
		chart.push(&dummy);
		while (!chart.empty())
		{
			EstadoCompilador* estado = chart.top();
			cout << "Proceso ";
			estado->produccionRef->print();
			if (terminoEstadoMal(estado))
			{
				acabaMal(estado, chart);
			}
			else if (terminoEstadoBien(estado))
			{
				acabaBien(estado, chart);
			}
			else if (sePuedeAplicar(estado))
				aplica(estado);
			else if (sePuedeExpandir(estado))
				expande(estado, chart);
			DBGstack(chart);
			cout << endl;
			// sleep(1);
		}
		return !dummy.fail;
	}

private:

	void aplica(EstadoCompilador* estado)
	{
		cout << "aplico" << endl;
		string noterminal = estado->produccionRef->der[0].text;
		int pos = estado->posPalabra;
		EstadoCompilador* padre = estado->origen;
		if (memcmp(&sentencia[pos], &noterminal[0], noterminal.size()) == 0) // TODO: no seguro
		{
			cout << "ESTA OK " << endl;
			padre->produccionRef->print();
			estado->posAsterico++;
			estado->posPalabra += noterminal.size();
		}
		else
		{
			cout << "FALLO" << endl;
			if (padre->tipo == NODO_AND)
				padre->fail = true;
			estado->fail = true;
		}
	}

	void expande(EstadoCompilador* estado, stack<EstadoCompilador*>& chart)
	{
		cout << "expando" << endl;
		vector<Produccion*> production_set = findProductions(estado);
		if (production_set.size() > 1) // Convierto nodo a tipo OR
		{
			cout << "convierto a OR" << endl;
			estado->tipo = NODO_OR;
			estado->fail = true;
		}
		for (Produccion* p : production_set)
		{
			EstadoCompilador* newstate = new EstadoCompilador{ p, 0, estado->posPalabra, estado, 0, false }; // Creo nodo tipo AND
			cout << "Push: ";
			newstate->produccionRef->print();
			chart.push(newstate);
		}
	}

	void acabaMal(EstadoCompilador* estado, stack<EstadoCompilador*>& chart)
	{
		cout << "Acabo malevolamente!" << endl;
		chart.pop();
		EstadoCompilador* padre = estado->origen;
		if (padre != nullptr)
			if (padre->tipo == NODO_AND)
				padre->fail = true;
	}

	void acabaBien(EstadoCompilador* estado, stack<EstadoCompilador*>& chart)
	{
		cout << "Acabo pacificamente!" << endl;
		chart.pop();
		EstadoCompilador* padre = estado->origen;
		if (padre != nullptr)
		{
			if (padre->tipo == NODO_OR)
				padre->fail = false;
			padre->posAsterico++;
			padre->posPalabra = estado->posPalabra;
		}
	}

	vector<Produccion*> findProductions(EstadoCompilador* estado)
	{
		string noterminalname = estado->produccionRef->der[estado->posAsterico].text;
		vector<Produccion*> producs;
		for (Produccion& p : gramatica.producciones)
		{
			if (p.izq == noterminalname)
			{
				producs.push_back(&p);
			}
		}
		return producs;
	}

	bool terminoEstadoBien(EstadoCompilador* estado)
	{
		return (estado->tipo == NODO_OR && estado->fail == false) || (estado->posAsterico >= estado->produccionRef->der.size());
	}

	bool terminoEstadoMal(EstadoCompilador* estado)
	{
		return (estado->tipo == NODO_OR && estado->fail == true) || (estado->tipo == NODO_AND && estado->fail == true);
	}

	bool sePuedeAplicar(EstadoCompilador* estado)
	{
		return estado->produccionRef->haveTerminals;
	}

	bool sePuedeExpandir(EstadoCompilador* estado)
	{
		return estado->posAsterico < estado->produccionRef->der.size();
	}

	void DBGstack(stack<EstadoCompilador*> stk)
	{
		cout << "^^^^^^^^^^^^^^^" << endl;
		while (!stk.empty())
		{
			EstadoCompilador* e = stk.top();
			e->produccionRef->print();
			stk.pop();
		}
		cout << "---------------" << endl;
	}
};



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
	BuilderGramatica builder;
	Gramatica G = builder.buildGramatica("gramatica.txt");
	Compilador compilador(G);
	G.print();
	string testcase = removeWhiteSpaces(userInput());

	if (compilador.esSentenciaValida(testcase))
		cout << "Sentencia valida" << endl;
	else
		cout << "Sentencia NO valida" << endl;
	return 0;
}
