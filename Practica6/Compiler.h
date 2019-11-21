#pragma once
#include <stack>
#include "Gramatica.h"
#include "EstadoCompilador.h"

class Compiler
{
private:
	Gramatica gramatica;
	string sentencia;
public:

	Compiler(Gramatica _gramatica);
	bool esSentenciaValida(string sentencia);
	void aplica(EstadoCompilador* estado);
	void expande(EstadoCompilador* estado, stack<EstadoCompilador*>& chart);
	void acabaMal(EstadoCompilador* estado, stack<EstadoCompilador*>& chart);
	void acabaBien(EstadoCompilador* estado, stack<EstadoCompilador*>& chart);
	vector<Produccion*> findProductions(EstadoCompilador* estado);
	bool terminoEstadoBien(EstadoCompilador* estado);
	bool terminoEstadoMal(EstadoCompilador* estado);
	bool sePuedeAplicar(EstadoCompilador* estado);
	bool sePuedeExpandir(EstadoCompilador* estado);
	void DBGstack(stack<EstadoCompilador*> stk);
};