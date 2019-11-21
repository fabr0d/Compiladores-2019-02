#pragma once
#include <string>
#include <map>
#include <iostream>
using namespace std;

struct Symbol
{
	string text;
	map<string, string> context;
	bool isTerminal;

	void build(string s)
	{
		if (s[0] != '\'')
		{
			isTerminal = false;
			int i = 0;
			while (s[i] != '[')
			{
				text += s[i++];
			}
			while (s[i] != ']')
			{
				i++;
				string fs, sc;
				while (s[i] != '=')
				{
					fs += s[i++];
				}
				i++;
				while (s[i] != ',' && s[i] != ']')
				{
					sc += s[i++];
				}
				context.insert(make_pair(fs, sc));
			}
		}
		else
		{
			isTerminal = true;
			int i = 1;
			while (s[i] != '\'')
			{
				text += s[i++];
			}
		}
	}

	string getNoTerminalText()
	{
		return text.substr(1, text.size() - 2);
	}

	string to_string() const
	{
		string s;
		if (!isTerminal)
		{
			s = text + "[";
			for (auto p : context)
			{
				s += p.first + "=" + p.second + ",";
			}
			s.erase(s.end() - 1);
			s += "]";
			return s;
		}
		else
		{
			s = "'" + text + "'";
		}
		return s;
	}
};


ostream& operator<<(ostream& o, const Symbol& symbol)
{
	return o << symbol.to_string();
}