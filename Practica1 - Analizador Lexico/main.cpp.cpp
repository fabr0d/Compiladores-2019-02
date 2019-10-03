//Hecho por Fabrizio Flores

#include <iostream>
#include <vector>

using namespace std;

void CharCopy(char* out, char* in, int n) // copia un char a otro char
{
	for (int i = 0; i < n; i++) { out[i] = in[i]; }	out[n] = '\0';
}

struct Token 
{
	char* palabra; //almacena una copia de la palabra
	int indice; //posicion en la oracion
	char tipo; //E(entero), V(variable), O(operador)
};

Token reconoceNumero(char** ptr) 
{
	Token token;
	bool revisar = true;
	int i = 0;
	int letras = 0;
	while ((revisar == true) && (*(*ptr + i) != '\0')) 
	{
		if ((*(*ptr + i) == '0') || (*(*ptr + i) == '1') || (*(*ptr + i) == '2') || (*(*ptr + i) == '3') || (*(*ptr + i) == '4') || 
			(*(*ptr + i) == '5') || (*(*ptr + i) == '6') || (*(*ptr + i) == '7') || (*(*ptr + i) == '8') || (*(*ptr + i) == '9')) 
		{
			letras++;
		}
		else 
		{
			revisar = false;
		}
		i++;
	}
	char* palabra = new char[letras + 1];

	CharCopy(palabra, *ptr, letras);
	
	token.palabra = palabra;
	token.indice = letras;
	token.tipo = 'E';	//entero
	return token;
}

Token reconoceVariable(char** ptr) 
{
	Token token;
	bool revisar = true;
	int i = 0;
	int letras = 0;

	while ((revisar == true) && (*(*ptr + i) != '\0')) 
	{
		if ((*(*ptr + i) == '0') || (*(*ptr + i) == '1') || (*(*ptr + i) == '2') || (*(*ptr + i) == '3') || (*(*ptr + i) == '4') || (*(*ptr + i) == '5') ||
			(*(*ptr + i) == '6') || (*(*ptr + i) == '7') || (*(*ptr + i) == '8') ||	(*(*ptr + i) == '9') ||

			(*(*ptr + i) == 'a') || (*(*ptr + i) == 'b') || (*(*ptr + i) == 'c') || (*(*ptr + i) == 'd') || (*(*ptr + i) == 'e') || (*(*ptr + i) == 'f') ||
			(*(*ptr + i) == 'g') || (*(*ptr + i) == 'h') || (*(*ptr + i) == 'i') || (*(*ptr + i) == 'j') || (*(*ptr + i) == 'k') || (*(*ptr + i) == 'l') ||
			(*(*ptr + i) == 'm') || (*(*ptr + i) == 'n') || (*(*ptr + i) == 'o') ||	(*(*ptr + i) == 'p') || (*(*ptr + i) == 'q') || (*(*ptr + i) == 'r') ||
			(*(*ptr + i) == 's') || (*(*ptr + i) == 't') || (*(*ptr + i) == 'u') ||	(*(*ptr + i) == 'v') || (*(*ptr + i) == 'w') || (*(*ptr + i) == 'x') ||
			(*(*ptr + i) == 'y') || (*(*ptr + i) == 'z') ||

			(*(*ptr + i) == 'A') || (*(*ptr + i) == 'B') || (*(*ptr + i) == 'C') ||	(*(*ptr + i) == 'D') || (*(*ptr + i) == 'E') || (*(*ptr + i) == 'F') ||
			(*(*ptr + i) == 'G') || (*(*ptr + i) == 'H') || (*(*ptr + i) == 'I') ||	(*(*ptr + i) == 'J') || (*(*ptr + i) == 'K') || (*(*ptr + i) == 'L') ||
			(*(*ptr + i) == 'M') || (*(*ptr + i) == 'N') || (*(*ptr + i) == 'O') ||	(*(*ptr + i) == 'P') || (*(*ptr + i) == 'Q') || (*(*ptr + i) == 'R') ||
			(*(*ptr + i) == 'S') || (*(*ptr + i) == 'T') || (*(*ptr + i) == 'U') ||	(*(*ptr + i) == 'V') || (*(*ptr + i) == 'W') || (*(*ptr + i) == 'X') ||
			(*(*ptr + i) == 'Y') || (*(*ptr + i) == 'Z')) 
		{
			letras++;
		}
		else 
		{
			revisar = false;
		}
		i++;
	}

	char* palabra = new char[letras + 1];
	CharCopy(palabra, *ptr, letras);
	token.palabra = palabra;
	token.indice = letras;
	token.tipo = 'V';	//variable
	return token;
}

vector<Token> analizadorLexico(char* linea) 
{
	vector<Token> tokens;
	Token token;
	int pos = 0;
	int tempo = 0;//guarda temporalmente las letras que recorre
	while (*linea != '\0') 
	{
		switch (*linea) 
		{
		case '0': case '1': case '2': case '3': case '4': case '5': case '6': case '7': case '8': case '9':
			token = reconoceNumero(&linea);
			tempo = token.indice;
			token.indice = pos;
			pos += tempo;
			tokens.push_back(token);
			linea += tempo;
			break;

		case 'a': case 'b': case 'c': case 'd': case 'e': case 'f': case 'g': case 'h': case 'i': case 'j': case 'k': case 'l': case 'm': case 'n': case 'o':
		case 'p': case 'q': case 'r': case 's': case 't': case 'u': case 'v': case 'w': case 'x': case 'y':	case 'z':
		case 'A': case 'B': case 'C': case 'D': case 'E': case 'F': case 'G': case 'H': case 'I': case 'J': case 'K': case 'L': case 'M': case 'N': case 'O':
		case 'P': case 'Q': case 'R': case 'S': case 'T': case 'U': case 'V': case 'W': case 'X': case 'Y': case 'Z':
			token = reconoceVariable(&linea);
			tempo = token.indice;
			token.indice = pos;
			pos += tempo;
			tokens.push_back(token);
			linea += tempo;
			break;
		default:
			pos++;
			linea++; //Significa que encontro un espacio en blanco
		}
	}
	return tokens;
}

int main() 
{
	char linea[256];
	cout << "Ingrese linea: " << endl;
	cin.getline(linea, 255, '\n');
	
	vector<Token> tokens = analizadorLexico(linea);

	for (int i = 0; i < tokens.size(); i++) 
	{
		cout<<i<<">  "<<" Token["<<i<<"].palabra: "<<tokens[i].palabra<<" Indice:["<<i<<"].indice : "<<tokens[i].indice<<" Tipo["<<i<<"].tipo: "<<tokens[i].tipo<<endl;
	}
	
	for (int i = 0; i < tokens.size(); i++) 
	{
		delete[] tokens[i].palabra;
	}
}