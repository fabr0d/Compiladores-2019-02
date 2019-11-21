#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <set>

#include "Gramatica.h"
#include "Produccion.h"

using namespace std;

vector<string> getLines(int lines);

Gramatica getGram(vector<string> lines);