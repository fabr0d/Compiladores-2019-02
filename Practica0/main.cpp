
////////////////////////////////////////////////////////////////////////////////   EJERCICIO 1 ////////////////////////////////////////////////////////////////////////////////////////////
/*
#include <iostream>
#include <string>
#include <algorithm> 
using namespace std;

int main() {
	string tokens;
	getline(cin, tokens);
	int x = 0;
	int y = 0;
	int cond = 0;
	for (int i = 0; i < tokens.size(); i++)
	{
		if (tokens[i] == ']' and cond == 2)
		{
			break;
		}
		if (tokens[i] == ')' and cond == 1)
		{
			break;
		}

		if (tokens[i] == '[')
		{
			x = i;
			cond = 1;
		}
		if (tokens[i] == ']' and cond == 1)
		{
			y = i;
			tokens.erase(x, 1);
			tokens.erase(y - 1, 1);
			cond = 0;
			i = -1;
		}
		if (tokens[i] == '(')
		{
			x = i;
			cond = 2;
		}
		if (tokens[i] == ')' and cond == 2)
		{
			y = i;
			tokens.erase(x, 1);
			tokens.erase(y - 1, 1);
			cond = 0;
			i = -1;
		}
	}
	if (tokens.size() == 0)
	{
		cout << "SI" << endl;
	}
	else {
		cout << "NO" << endl;
	}
	return 0;
}
*/
////////////////////////////////////////////////////////////////////////////////   EJERCICIO 2 ////////////////////////////////////////////////////////////////////////////////////////////
/*
#include <iostream>
#include <string>
#include <algorithm> 
#include <vector>
using namespace std;

vector<string> vocales = { "a","e","i","o","u" };

string special_cases(string verbo)
{
	if (verbo=="reir")
	{
		return "riendo";
	}
}

string gerundio_gen(string verbo)
{
	string infinitivo;
	verbo.erase(verbo.size() - 1, 1);
	infinitivo = infinitivo + verbo[verbo.size() - 2];
	infinitivo = infinitivo + verbo[verbo.size() - 1];
	cout << "infinitivo: " << infinitivo << endl;

	if (infinitivo == "ar")
	{
		string answer;
		answer.assign(verbo, 0, verbo.size() - 2);
		answer = answer + "ando";
		return answer;
	}
	if (infinitivo == "er")
	{
		string answer;
		answer.assign(verbo, 0, verbo.size() - 2);
		if (answer[answer.size()-1]=='a' or answer[answer.size() - 1] == 'e' or answer[answer.size() - 1] == 'i' or answer[answer.size() - 1] == 'o' or answer[answer.size() - 1] == 'u')
		{
			return answer + "yendo";
		}
		else
		{
			return answer + "iendo";
		}
	}
	if (infinitivo == "ir")
	{
		string answer;
		answer.assign(verbo, 0, verbo.size() - 2);
		if (answer[answer.size() - 1] == 'a' or answer[answer.size() - 1] == 'e' or answer[answer.size() - 1] == 'i' or answer[answer.size() - 1] == 'o' or answer[answer.size() - 1] == 'u')
		{
			return answer + "yendo";
		}
		else
		{
			return answer + "endo";
		}
	}
}

int main()
{
	string line;
	getline(cin, line);
	int space;

	string verbo;
	string gerundio;

	for (int i = 0; i < line.size(); i++)
	{
		if (line[i]==' ')
		{
			space = i + 1;
			cout << "espacio detectado en: " << space << endl;
			break;
		}
	}
	verbo.assign(line, 0, space);
	gerundio.assign(line, space, (line.size()-1));
	cout << "verbo : " << verbo << endl;
	cout << "gerundio: " << gerundio << endl;

	if (gerundio == gerundio_gen(verbo))
	{
		cout << "SI" << endl;
	}
	else
	{
		cout << "NO" << endl;
	}
}
*/

////////////////////////////////////////////////////////////////////////////////   EJERCICIO 3 ////////////////////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <string>
#include <algorithm> 
#include <vector>
#include <iomanip>
using namespace std;

void problems_solver(string problem)
{
	string dataP; //unidad W
	string dataU; //unidad V
	string dataI; //unidad A

	//M = mega que es *1000000
	//m = mili que es *(1/1000)
	//k = kilo que es *1000

	for (int i = 0; i < problem.size(); i++)
	{
		if (problem[i] == 'P' and problem[i + 1] == '=')
		{
			int j = i;
			while (problem[j] != 'W')
			{
				dataP = dataP + problem[j];
				j++;
			}
			dataP = dataP + "W";
		}
		if (problem[i] == 'U' and problem[i + 1] == '=')
		{
			int j = i;
			while (problem[j] != 'V')
			{
				dataU = dataU + problem[j];
				j++;
			}
			dataU = dataU + "V";
		}
		if (problem[i] == 'I' and problem[i + 1] == '=')
		{
			int j = i;
			while (problem[j] != 'A')
			{
				dataI = dataI + problem[j];
				j++;
			}
			dataI = dataI + "A";
		}
	}

	if (dataP.size() == 0) //tengo que hallar P ; P = U * I
	{
		//cout << "dataU: " << dataU << endl;
		//cout << "dataI: " << dataI << endl;
		long double valueU = 0;
		long double valueI = 0;

		string tempU;
		string::size_type sz1;
		tempU = dataU;
		tempU.erase(0, 2);
		tempU.erase(tempU.size()-1, 1);

		if (tempU[tempU.size() - 1] == 'M')
		{
			tempU.erase(tempU.size() - 1, 1);
			valueU = stod(tempU, &sz1);
			valueU = valueU * 1000000;
		}
		else if (tempU[tempU.size() - 1] == 'm')
		{
			tempU.erase(tempU.size() - 1, 1);
			valueU = stod(tempU, &sz1);
			valueU = valueU * (1 / 1000);
		}
		else if (tempU[tempU.size() - 1] == 'k')
		{
			tempU.erase(tempU.size() - 1, 1);
			valueU = stod(tempU, &sz1);
			valueU = valueU * 1000;
		}
		else
		{
			valueU = stod(tempU, &sz1);
		}
		

		string tempI;
		string::size_type sz2;
		tempI = dataI;
		tempI.erase(0, 2);
		tempI.erase(tempI.size() - 1, 1);

		if (tempI[tempI.size() - 1] == 'M')
		{
			tempI.erase(tempI.size() - 1, 1);
			valueI = stod(tempI, &sz2);
			valueI = valueI * 1000000;
		}
		else if (tempI[tempI.size() - 1] == 'm')
		{
			tempI.erase(tempI.size() - 1, 1);
			valueI = stod(tempI, &sz2);
			valueI = valueI * (1 / 1000);
		}
		else if (tempI[tempI.size() - 1] == 'k')
		{
			tempI.erase(tempI.size() - 1, 1);
			valueI = stod(tempI, &sz2);
			valueI = valueI * 1000;
		}
		else
		{
			valueI = stod(tempI, &sz2);
		}


		long double valueP = valueI * valueU;
		cout << "P=" << fixed << setprecision(2) << valueP << "W" << endl;
		//cout << "" << endl;
	}
	if (dataU.size() == 0) //tengo que hallar U ; U = P / I
	{
		//cout << "dataP: " << dataP << endl;
		//cout << "dataI: " << dataI << endl;
		long double valueP = 0;
		long double valueI = 0;

		string tempP;
		string::size_type sz1;
		tempP = dataP;
		tempP.erase(0, 2);
		tempP.erase(tempP.size() - 1, 1);

		if (tempP[tempP.size() - 1] == 'M')
		{
			tempP.erase(tempP.size() - 1, 1);
			valueP = stod(tempP, &sz1);
			valueP = valueP * 1000000;
		}
		else if (tempP[tempP.size() - 1] == 'm')
		{
			tempP.erase(tempP.size() - 1, 1);
			valueP = stod(tempP, &sz1);
			valueP = valueP * (1 / 1000);
		}
		else if (tempP[tempP.size() - 1] == 'k')
		{
			tempP.erase(tempP.size() - 1, 1);
			valueP = stod(tempP, &sz1);
			valueP = valueP * 1000;
		}
		else
		{
			valueP = stod(tempP, &sz1);
		}


		string tempI;
		string::size_type sz2;
		tempI = dataI;
		tempI.erase(0, 2);
		tempI.erase(tempI.size() - 1, 1);

		if (tempI[tempI.size() - 1] == 'M')
		{
			tempI.erase(tempI.size() - 1, 1);
			valueI = stod(tempI, &sz2);
			valueI = valueI * 1000000;
		}
		else if (tempI[tempI.size() - 1] == 'm')
		{
			tempI.erase(tempI.size() - 1, 1);
			valueI = stod(tempI, &sz2);
			valueI = valueI * (1 / 1000);
		}
		else if (tempI[tempI.size() - 1] == 'k')
		{
			tempI.erase(tempI.size() - 1, 1);
			valueI = stod(tempI, &sz2);
			valueI = valueI * 1000;
		}
		else
		{
			valueI = stod(tempI, &sz2);
		}


		long double valueU = valueP / valueI;
		cout << "U=" << fixed << setprecision(2) << valueU << "V" << endl;
		//cout << "" << endl;
	}
	if (dataI.size() == 0) //tengo que hallar I ; I = P / U
	{
		//cout << "dataP: " << dataP << endl;
		//cout << "dataU: " << dataU << endl;
		long double valueP = 0;
		long double valueU = 0;

		string tempP;
		string::size_type sz1;
		tempP = dataP;
		tempP.erase(0, 2);
		tempP.erase(tempP.size() - 1, 1);

		if (tempP[tempP.size() - 1] == 'M')
		{
			tempP.erase(tempP.size() - 1, 1);
			valueP = stod(tempP, &sz1);
			valueP = valueP * 1000000;
		}
		else if (tempP[tempP.size() - 1] == 'm')
		{
			tempP.erase(tempP.size() - 1, 1);
			valueP = stod(tempP, &sz1);
			valueP = valueP * (1 / 1000);
		}
		else if (tempP[tempP.size() - 1] == 'k')
		{
			tempP.erase(tempP.size() - 1, 1);
			valueP = stod(tempP, &sz1);
			valueP = valueP * 1000;
		}
		else
		{
			valueP = stod(tempP, &sz1);
		}

		string tempU;
		string::size_type sz2;
		tempU = dataU;
		tempU.erase(0, 2);
		tempU.erase(tempU.size() - 1, 1);

		if (tempU[tempU.size() - 1] == 'M')
		{
			tempU.erase(tempU.size() - 1, 1);
			valueU = stod(tempU, &sz2);
			valueU = valueU * 1000000;
		}
		else if (tempU[tempU.size() - 1] == 'm')
		{
			tempU.erase(tempU.size() - 1, 1);
			valueU = stod(tempU, &sz2);
			valueU = valueU * (1 / 1000);
		}
		else if (tempU[tempU.size() - 1] == 'k')
		{
			tempU.erase(tempU.size() - 1, 1);
			valueU = stod(tempU, &sz2);
			valueU = valueU * 1000;
		}
		else
		{
			valueU = stod(tempU, &sz2);
		}

		long double valueI = valueP / valueU;
		cout << "I=" << fixed << setprecision(2) << valueI << "A" << endl;
		//cout << "" << endl;
	}
}

int main()
{
	int loops;
	cin>>loops;
	vector<string> problems;
	string tmp;
	loops++;
	while (loops!=0)
	{
		getline(cin, tmp);
		problems.push_back(tmp);
		loops--;
	}
	problems.erase(problems.begin());
	int j = 0;
	while (j<problems.size())
	{
		if (j!=0)
		{
			cout << "" << endl;
		}
		cout << "Problem #" << j + 1 << endl;
		problems_solver(problems[j]);
		j++;
	}

}