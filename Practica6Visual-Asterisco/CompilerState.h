#pragma once

#include "Production.h"

struct CompilerState
{
	Produccion* produccionRef;
	int posAsterico;
	int posPalabra;
	CompilerState* origen;
	bool fail;

	CompilerState(Produccion* produccionRef, int posPalabra, CompilerState* origen)
	{
		this->produccionRef = produccionRef;
		this->posPalabra = posPalabra;
		this->posAsterico = 0;
		this->origen = origen;
		this->fail = false;
	}
};