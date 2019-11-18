#pragma once
#include <string>
#include <iostream>
using namespace std;

struct tokenContext
{
	string text;
	bool isTerminal;

	tokenContext(string text);
	void print_tokenContext();
};