#pragma once
#include "Produccion.h"

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