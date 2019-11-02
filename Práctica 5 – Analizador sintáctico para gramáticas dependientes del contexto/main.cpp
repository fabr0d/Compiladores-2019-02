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
class tokenContext
{
public:
	string nombre;
	map<string, string> contexto;
	bool isTerminal;
};

class Produccion
{
public:
	tokenContext izq;
	vector<tokenContext> der;
};

class Gramatica
{
public:
	vector<Produccion> productiones;
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

void printVector(vector<tokenContext> vec)
{
	for (int i = 0; i < vec.size(); i++)
	{
		cout << vec[i].nombre << " ";
	}
	cout << endl;
}

tokenContext GenTokenContext(string text)
{
	text.erase(remove_if(text.begin(), text.end(), ::isspace), text.end()); //borrar espacios
	//tendremos un string con la estructura: texto [ contexto ]
	string corI("[");
	string corD("]");

	size_t foundCI = text.find(corI);
	size_t foundCD = text.find(corD);

	if (foundCI == -1 && foundCD == -1) // es un terminal y no tiene contexto
	{
		tokenContext temp;
		temp.nombre = text;
		temp.isTerminal = true;
		return temp;
	}
	else
	{
		string texto = text.substr(0, foundCI - 0);
		string contexto = text.substr(foundCI + 1, foundCD - foundCI - 1);

		string coma(",");
		size_t foundCOMA = contexto.find(coma);

		if (foundCOMA == -1) //no hay comas
		{
			tokenContext temp2;
			temp2.nombre = texto;
			temp2.isTerminal = false;

			string igual("=");
			size_t foundIG = contexto.find(igual);
			//categoria = valor
			string categoria = contexto.substr(0, foundIG);
			string valor = contexto.substr(foundIG + 1, (contexto.size() - 1) - foundIG);

			map<string, string>::iterator it = temp2.contexto.begin();
			temp2.contexto.insert(it, pair<string, string>(categoria, valor));
			return temp2;
		}
		else				//hay comas
		{
			tokenContext temp3;
			temp3.nombre = texto;
			temp3.isTerminal = false;

			vector<string> varioscontextos;

			//separo el string por sus comas
			string stempcon = contexto;
			string delimiter = ",";
			size_t pos = 0;
			string token;
			while ((pos = stempcon.find(delimiter)) != string::npos)
			{
				token = stempcon.substr(0, pos);
				varioscontextos.push_back(token);
				stempcon.erase(0, pos + delimiter.length());
			}
			varioscontextos.push_back(stempcon);

			//inserto los contextos en el map
			for (size_t i = 0; i < varioscontextos.size(); i++)
			{
				string igual("=");
				size_t foundIG = varioscontextos[i].find(igual);
				//categoria = valor
				string categoria = varioscontextos[i].substr(0, foundIG);
				string valor = varioscontextos[i].substr(foundIG + 1, (varioscontextos[i].size() - 1) - foundIG);

				map<string, string>::iterator it = temp3.contexto.begin();
				temp3.contexto.insert(it, pair<string, string>(categoria, valor));
			}
			return temp3;
		}
	}
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
		izquierda.erase(remove_if(izquierda.begin(), izquierda.end(), ::isspace), izquierda.end());//borrar espacios

		//Subdivide el string derecho por espacios y los almacena en un vector
		vector<string> derecha_list;
		istringstream iss(derecha);
		for (string derecha; iss >> derecha; )
		{
			derecha_list.push_back(derecha);
		}

		//verificar si hay operador "|" y lo vuelve a subdividir
		vector<vector<tokenContext>> derechas_por_o;
		vector<tokenContext> temporal;	//string temporal
		while (derecha_list.size() > 0)
		{
			if (derecha_list[0] == "|")
			{
				//se encontro una "|"
				derecha_list.erase(derecha_list.begin());	//borra el primero
				derechas_por_o.push_back(temporal);
				temporal.clear();
			}
			else
			{
				//no se encontro una "|"
				temporal.push_back(GenTokenContext(derecha_list[0]));
				derecha_list.erase(derecha_list.begin());
				if (derecha_list.size() == 0)
				{
					//se vacio todas las derechas
					derechas_por_o.push_back(temporal);
					temporal.clear();
				}
			}
		}

		//tenemos a un string en izquierda
		//tenemos un vector de string de derechas que corresponden al string izquierdo

		//generaremos un tokenContext
		tokenContext tempIzq = GenTokenContext(izquierda);

		//Generacion de las producciones
		for (int i = 0; i < derechas_por_o.size(); i++)
		{
			Produccion p1;
			p1.izq = tempIzq;
			p1.der = derechas_por_o[i];

			//send produccion to grammar
			rpta.productiones.push_back(p1);
		}
	}

	//cout << "Numero de producciones: " << rpta.production.size() << endl;

	set<string>terminalesrtpa;
	set<string>noterminalesrtpa;
	//verificar cuales son terminales o no terminales
	for (int i = 0; i < rpta.productiones.size(); i++)
	{
		terminalesrtpa.insert(rpta.productiones[i].izq.nombre);
	}
	rpta.terminales = terminalesrtpa;
	for (int i = 0; i < rpta.productiones.size(); i++)
	{
		for (int j = 0; j < rpta.productiones[i].der.size(); j++)
		{
			//Si no hay ocurrencias en mi set de terminales de la produccion de la derecha
			if (rpta.terminales.count(rpta.productiones[i].der[j].nombre) == 0)
			{
				//lo meto en el set de no terminales
				rpta.noterminales.insert(rpta.productiones[i].der[j].nombre);
			}
		}
	}

	return rpta;
}

void printProduccion(Produccion pro)
{
	cout << pro.izq.nombre << " := ";
	printVector(pro.der);
}

void printGramatica(Gramatica grammar)
{
	cout << "Producciones: " << endl;
	for (int i = 0; i < grammar.productiones.size(); i++)
	{
		printProduccion(grammar.productiones[i]);
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
	printGramatica(Grammar1);

	/*AnalizadorSintacticoLL1 ll1;
	ll1.llenarTAS();
	string cadena;
	getline(cin, cadena);
	cout << ll1.reconocerSentencia(cadena) << endl;*/
}