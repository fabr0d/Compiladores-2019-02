#include "tokenContext.h"

tokenContext::tokenContext(string text)
{
	isTerminal = text[0] == '\'';
	if (isTerminal)
	{
		this->text = text.substr(1, text.size() - 2);
	}
	else
	{
		this->text = text;
	}
}

void tokenContext::print_tokenContext()
{
	cout << "token_name: " << text << endl;
	cout << "is_terminal?: " << isTerminal << endl;
}