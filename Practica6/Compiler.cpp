#include "Compiler.h"

Compiler::Compiler(Gramatica _gramatica)
{
	gramatica = _gramatica;
}

bool Compiler::esSentenciaValida(string sentencia)
{
	this->sentencia = sentencia;
	EstadoCompilador dummy{ &gramatica.dummy, 0, 0, nullptr, NODO_AND, false };
	stack<EstadoCompilador*> chart;
	chart.push(&dummy);
	while (!chart.empty())
	{
		EstadoCompilador* estado = chart.top();
		cout << "Proceso ";
		estado->produccionRef->print_Produccion();
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

void Compiler::aplica(EstadoCompilador* estado)
{
	cout << "aplico" << endl;
	string noterminal = estado->produccionRef->der[0].text;
	int pos = estado->posPalabra;
	EstadoCompilador* padre = estado->origen;
	if (memcmp(&sentencia[pos], &noterminal[0], noterminal.size()) == 0) // TODO: no seguro
	{
		cout << "ESTA OK " << endl;
		padre->produccionRef->print_Produccion();
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

void Compiler::expande(EstadoCompilador* estado, stack<EstadoCompilador*>& chart)
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
		newstate->produccionRef->print_Produccion();
		chart.push(newstate);
	}
}

void Compiler::acabaMal(EstadoCompilador* estado, stack<EstadoCompilador*>& chart)
{
	cout << "Acabo malevolamente!" << endl;
	chart.pop();
	EstadoCompilador* padre = estado->origen;
	if (padre != nullptr)
		if (padre->tipo == NODO_AND)
			padre->fail = true;
}

void Compiler::acabaBien(EstadoCompilador* estado, stack<EstadoCompilador*>& chart)
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

vector<Produccion*> Compiler::findProductions(EstadoCompilador* estado)
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

bool Compiler::terminoEstadoBien(EstadoCompilador* estado)
{
	return (estado->tipo == NODO_OR && estado->fail == false) || (estado->posAsterico >= estado->produccionRef->der.size());
}

bool Compiler::terminoEstadoMal(EstadoCompilador* estado)
{
	return (estado->tipo == NODO_OR && estado->fail == true) || (estado->tipo == NODO_AND && estado->fail == true);
}

bool Compiler::sePuedeAplicar(EstadoCompilador* estado)
{
	return estado->produccionRef->haveTerminals;
}

bool Compiler::sePuedeExpandir(EstadoCompilador* estado)
{
	return estado->posAsterico < estado->produccionRef->der.size();
}

void Compiler::DBGstack(stack<EstadoCompilador*> stk)
{
	cout << "^^^^^^^^^^^^^^^" << endl;
	while (!stk.empty())
	{
		EstadoCompilador* e = stk.top();
		e->produccionRef->print_Produccion();
		stk.pop();
	}
	cout << "---------------" << endl;
}