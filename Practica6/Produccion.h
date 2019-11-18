#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "tokenContext.h"
using namespace std;

class Produccion
{
public:
	string izq;
	vector<tokenContext> der;
	bool haveTerminals;

	Produccion() = default;
	Produccion(string _izq, vector<tokenContext> _der);
	void print_Produccion();
};