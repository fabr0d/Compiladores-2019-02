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
//#include <string.h> //strncpy

using namespace std;

typedef pair<int, int> Coord;

queue<string> separateValues(string input, char label) {
	stringstream inputstream(input);
	string value;
	queue<string> values;
	while (getline(inputstream, value, label)) {
		values.push(value);
	}
	return values;
}


//AL Begin

void strCopy(char* a_out, char* a_in, int n) {
	for (int i = 0; i < n; i++) {
		a_out[i] = a_in[i];
	}
	a_out[n] = '\0';
}

struct Token {
	char* palabra; //almacena una copia de la palabra
	int indice;
	char tipo; //E(entero), V(variable), O(operador), I(igual),
	//L(parentesis_izquierdo, R(parentesis_derecho)
};

Token reconoceNumero(char** ptr) {
	Token token;
	bool revisar = true;
	int i = 0;
	int letras = 0;
	while ((revisar == true) && (*(*ptr + i) != '\0')) {
		if ((*(*ptr + i) == '0') || (*(*ptr + i) == '1') || (*(*ptr + i) == '2') ||
			(*(*ptr + i) == '3') || (*(*ptr + i) == '4') || (*(*ptr + i) == '5') ||
			(*(*ptr + i) == '6') || (*(*ptr + i) == '7') || (*(*ptr + i) == '8') ||
			(*(*ptr + i) == '9')) {
			letras++;
		}
		else {
			revisar = false;
		}
		i++;
	}
	char* palabra = new char[letras + 1];
	strCopy(palabra, *ptr, letras);
	token.palabra = palabra;
	token.indice = letras;
	token.tipo = 'E';
	return token;
}

Token reconoceVariable(char** ptr) {
	Token token;
	bool revisar = true;
	int i = 0;
	int letras = 0;
	while ((revisar == true) && (*(*ptr + i) != '\0')) {
		if ((*(*ptr + i) == '0') || (*(*ptr + i) == '1') || (*(*ptr + i) == '2') ||
			(*(*ptr + i) == '3') || (*(*ptr + i) == '4') || (*(*ptr + i) == '5') ||
			(*(*ptr + i) == '6') || (*(*ptr + i) == '7') || (*(*ptr + i) == '8') ||
			(*(*ptr + i) == '9') ||
			(*(*ptr + i) == 'a') || (*(*ptr + i) == 'b') || (*(*ptr + i) == 'c') ||
			(*(*ptr + i) == 'd') || (*(*ptr + i) == 'e') || (*(*ptr + i) == 'f') ||
			(*(*ptr + i) == 'g') || (*(*ptr + i) == 'h') || (*(*ptr + i) == 'i') ||
			(*(*ptr + i) == 'j') || (*(*ptr + i) == 'k') || (*(*ptr + i) == 'l') ||
			(*(*ptr + i) == 'm') || (*(*ptr + i) == 'n') || (*(*ptr + i) == 'o') ||
			(*(*ptr + i) == 'p') || (*(*ptr + i) == 'q') || (*(*ptr + i) == 'r') ||
			(*(*ptr + i) == 's') || (*(*ptr + i) == 't') || (*(*ptr + i) == 'u') ||
			(*(*ptr + i) == 'v') || (*(*ptr + i) == 'w') || (*(*ptr + i) == 'x') ||
			(*(*ptr + i) == 'y') || (*(*ptr + i) == 'z') ||
			(*(*ptr + i) == 'A') || (*(*ptr + i) == 'B') || (*(*ptr + i) == 'C') ||
			(*(*ptr + i) == 'D') || (*(*ptr + i) == 'E') || (*(*ptr + i) == 'F') ||
			(*(*ptr + i) == 'G') || (*(*ptr + i) == 'H') || (*(*ptr + i) == 'I') ||
			(*(*ptr + i) == 'J') || (*(*ptr + i) == 'K') || (*(*ptr + i) == 'L') ||
			(*(*ptr + i) == 'M') || (*(*ptr + i) == 'N') || (*(*ptr + i) == 'O') ||
			(*(*ptr + i) == 'P') || (*(*ptr + i) == 'Q') || (*(*ptr + i) == 'R') ||
			(*(*ptr + i) == 'S') || (*(*ptr + i) == 'T') || (*(*ptr + i) == 'U') ||
			(*(*ptr + i) == 'V') || (*(*ptr + i) == 'W') || (*(*ptr + i) == 'X') ||
			(*(*ptr + i) == 'Y') || (*(*ptr + i) == 'Z')) {
			letras++;
		}
		else {
			revisar = false;
		}
		i++;
	}
	char* palabra = new char[letras + 1];
	strCopy(palabra, *ptr, letras);
	token.palabra = palabra;
	token.indice = letras;
	token.tipo = 'V';
	return token;
}

Token reconoceOperador(char** ptr) {
	Token token;
	char* palabra = new char[2];
	strCopy(palabra, *ptr, 1);
	token.palabra = palabra;
	token.indice = 1;
	token.tipo = 'O';
	return token;
}

Token reconoceIgual(char** ptr) {
	Token token;
	char* palabra = new char[2];
	strCopy(palabra, *ptr, 1);
	token.palabra = palabra;
	token.indice = 1;
	token.tipo = 'I';
	return token;
}

Token reconoceLParentesis(char** ptr) {
	Token token;
	char* palabra = new char[2];
	strCopy(palabra, *ptr, 1);
	token.palabra = palabra;
	token.indice = 1;
	token.tipo = 'L';
	return token;
}

Token reconoceRParentesis(char** ptr) {
	Token token;
	char* palabra = new char[2];
	strCopy(palabra, *ptr, 1);
	token.palabra = palabra;
	token.indice = 1;
	token.tipo = 'R';
	return token;
}

vector<Token> analizadorLexico(char* linea) {
	vector<Token> tokens;
	Token token;
	int pos = 0;
	int sz = 0;
	while (*linea != '\0') {
		switch (*linea) {
		case '0': case '1': case '2': case '3': case '4':
		case '5': case '6': case '7': case '8': case '9':
			token = reconoceNumero(&linea);
			sz = token.indice;
			token.indice = pos;
			pos += sz;
			tokens.push_back(token);
			linea += sz;
			break;
		case 'a': case 'b': case 'c': case 'd': case 'e':
		case 'f': case 'g': case 'h': case 'i': case 'j':
		case 'k': case 'l': case 'm': case 'n': case 'o':
		case 'p': case 'q': case 'r': case 's': case 't':
		case 'u': case 'v': case 'w': case 'x': case 'y':
		case 'z':
		case 'A': case 'B': case 'C': case 'D': case 'E':
		case 'F': case 'G': case 'H': case 'I': case 'J':
		case 'K': case 'L': case 'M': case 'N': case 'O':
		case 'P': case 'Q': case 'R': case 'S': case 'T':
		case 'U': case 'V': case 'W': case 'X': case 'Y':
		case 'Z':
			token = reconoceVariable(&linea);
			sz = token.indice;
			token.indice = pos;
			pos += sz;
			tokens.push_back(token);
			linea += sz;
			break;
		case '+': case '-': case '*': case '/':
			token = reconoceOperador(&linea);
			sz = token.indice;
			token.indice = pos;
			pos += sz;
			tokens.push_back(token);
			linea += sz;
			break;
		case '=':
			token = reconoceIgual(&linea);
			sz = token.indice;
			token.indice = pos;
			pos += sz;
			tokens.push_back(token);
			linea += sz;
			break;
		case '(':
			token = reconoceLParentesis(&linea);
			sz = token.indice;
			token.indice = pos;
			pos += sz;
			tokens.push_back(token);
			linea += sz;
			break;
		case ')':
			token = reconoceRParentesis(&linea);
			sz = token.indice;
			token.indice = pos;
			pos += sz;
			tokens.push_back(token);
			linea += sz;
			break;
		default:
			pos++;
			linea++; //Significa que encontro un espacio en blanco
		}
	}
	return tokens;
}
//AL End

//Analizadores sintáctico descendente recursivo predictivo INICIO
class ProdContexto
{
	string nombre;
	map<string, string> contexto;
	bool act = false;
};

class Produccion
{
public:
	//ProdContexto izq;
	string izq;
	vector<string> der;
};

class Gramatica
{
public:
	vector<Produccion> production;
	set<string> terminales;
	set<string> noterminales;
	string estadoInicial;
};

void printSet(set<string> list)
{
	for (auto it = list.begin(); it != list.end(); ++it)
		cout << *it << ", ";
	cout << endl;
}

void printVector(vector<string> vec)
{
	for (int i = 0; i < vec.size(); i++)
	{
		cout << vec[i] << " ";
	}
	cout << endl;
}

Gramatica getGram(vector<string> grammar)
{
	Gramatica rpta;

	//Delimitador de la parte derecha y la parte izquierda
	string str1("->"); 

	for (int i = 0; i < grammar.size(); i++) //bucle por la cantidad de lineas en la gramtica
	{
		//found es la posicion en la que se encuentra el delimitador
		size_t found = grammar[i].find(str1);

		//derecha es la parte antes del delimitador(entre terminales y no terminales) se verificara por |
		string derecha = grammar[i].substr(found + 2, grammar[i].size() - 1);

		//derecha es la parte despues del delimitador(no terminales)
		string izquierda = grammar[i].substr(0, found - 1);
		izquierda.erase(remove_if(izquierda.begin(), izquierda.end(), ::isspace), izquierda.end());


		vector<string> derecha_list;
		istringstream iss(derecha);
		for (string derecha; iss >> derecha; )
		{
			derecha_list.push_back(derecha);
		}
		cout << "derechas / posibles no terminales y terminales: ";
		printVector(derecha_list);		

		//verificar si hay operador "|"
		vector<vector<string>> derechas_por_o;
		vector<string> temporal;//string temporal
		while (derecha_list.size() > 0)
		{
			if (derecha_list[0] == "|")
			{
				//cout << "se encontro una o" << endl;
				derecha_list.erase(derecha_list.begin());//borra el primero
				derechas_por_o.push_back(temporal);
				temporal.clear();
			}
			else
			{
				//cout << "no es una o asi que fresh" << endl;
				temporal.push_back(derecha_list[0]);
				derecha_list.erase(derecha_list.begin());
				if (derecha_list.size() == 0)
				{
					//cout << "se vacio todas las derechas" << endl;
					derechas_por_o.push_back(temporal);
					temporal.clear();
				}
			}
		}
		//cout << "numero de derechas separadas por el o: " <<derechas_por_o.size()<< endl;
		//gen produccion
		for (int i = 0; i < derechas_por_o.size(); i++)
		{
			Produccion p1;
			p1.izq = izquierda;
			p1.der = derechas_por_o[i];

			//send produccion to grammar
			rpta.production.push_back(p1);
		}
	}

	//cout << "Numero de producciones: " << rpta.production.size() << endl;

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

void printProduccion(Produccion pro)
{
	cout << pro.izq << " := ";
	printVector(pro.der);
}

void printGramatica(Gramatica grammar)
{
	cout << "Producciones: " << endl;
	for (int i = 0; i < grammar.production.size(); i++)
	{
		printProduccion(grammar.production[i]);
	}
	cout << endl;
	cout << "Terminales: " << endl;
	printSet(grammar.terminales);
	cout << "No terminales: " << endl;
	printSet(grammar.noterminales);

}

class AnalizadorSintacticoLL1 {
private:
	Gramatica gr;
	map<string, map<string, vector<string>>> tas;
	void adicionar(string noTerminal, string terminal, vector<string> prods);
	const string DOLAR = "$";
public:
	void llenarTAS();
	bool reconocerSentencia(string cadena);
};

void AnalizadorSintacticoLL1::adicionar(string noTerminal, string terminal, vector<string> prods) {
	tas[noTerminal][terminal] = prods;
}

void AnalizadorSintacticoLL1::llenarTAS() {
	adicionar("E", "(", { "T","Ep" });
	adicionar("E", "num", { "T","Ep" });
	adicionar("E", "id", { "T","Ep" });

	adicionar("Ep", DOLAR, { "^" });
	adicionar("Ep", ")", { "^" });
	adicionar("Ep", "+", { "+","T","Ep" });

	adicionar("T", "(", { "F","Tp" });
	adicionar("T", "num", { "F","Tp" });
	adicionar("T", "id", { "F","Tp" });

	adicionar("Tp", DOLAR, { "^" });
	adicionar("Tp", ")", { "^" });
	adicionar("Tp", "*", { "*","F","Tp" });
	adicionar("Tp", "+", { "^" });

	adicionar("F", "(", { "(","E",")" });
	adicionar("F", "num", { "num" });
	adicionar("F", "id", { "id" });
}

bool AnalizadorSintacticoLL1::reconocerSentencia(string cadena) {
	queue<string> entrada = separateValues(cadena, ' ');
	stack<string> pila;
	pila.push(DOLAR);
	pila.push(gr.estadoInicial);
	entrada.push(DOLAR);
	while ((!entrada.empty()) && (!pila.empty())) {
		if (entrada.front() == pila.top()) {
			entrada.pop();
			pila.pop();
		}
		else {
			string tmp = pila.top();
			pila.pop();
			for (auto x : tas[tmp][entrada.front()]) {
				if (x != "^") {
					pila.push(x);
				}
			}
		}
	}
	return entrada.empty() && pila.empty();
}

int main() {
	/*
	char linea[256];
	cout << "Ingrese linea: " << endl;
	cin.getline(linea, 255, '\n');
	vector<Token> tokens = analizadorLexico(linea);
	for (int i = 0; i < tokens.size(); i++) {
		cout << i << ">>> " <<
			" Palabra: " << tokens[i].palabra <<
			" Indice: " << tokens[i].indice <<
			" Tipo: " << tokens[i].tipo << endl;
	}
	//delete
	for (int i = 0; i < tokens.size(); i++) {
		delete[] tokens[i].palabra;
	}
	*/

	int lines;
	cout << "ingrese el numero de lineas de su gramatica: ";
	cin >> lines;
	string tempo;
	vector<string> grammar;
	cout << "ahora ingrese linea por linea" << endl;
	cin.ignore();
	for (size_t i = 0; i < lines; i++)
	{
		getline(cin, tempo);
		grammar.push_back(tempo);
	}

	Gramatica Grammar1 = getGram(grammar);
	cout << endl;
	//printGramatica(Grammar1);

	/*AnalizadorSintacticoLL1 ll1;
	ll1.llenarTAS();
	string cadena;
	getline(cin, cadena);
	cout << ll1.reconocerSentencia(cadena) << endl;*/
}