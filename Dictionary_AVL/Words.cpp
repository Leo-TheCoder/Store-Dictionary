#include "Words.h"

Words::Words()
{
}

Words::~Words()
{
}

Words::Words(const Words& s)
{
	name = s.name;
	meaning = s.meaning;
}

bool Words::readWord(string sentence)
{
	size_t pos;
	pos = sentence.find("  ");
	if (pos != string::npos)
	{
		name = sentence.substr(0, pos);
		meaning = sentence.substr(pos + 2);
		return true;
	}
	else
	{
		name = sentence;
		meaning = "";
		return false;
	}
}

void Words::inputWord()
{
	cout << "Please write your word: ";
	getline(cin, name);
	for (int i = 0; i < name.length(); i++)
	{
		
	}
	cout << "Please write your word's meaning: ";
	getline(cin, meaning);
}

void Words::modifyMeaning()
{
	cout << "Please write your new meaning for '" << name << "' word: ";
	getline(cin, meaning);
	cout << "Modified!" << endl;
}

string Words::getMeaning()
{
	return meaning;
}

void Words::standardize()
{	
	char c = name[0];
	while ((c < 'a' || c > 'z') && (c < 'A' || c > 'Z') && c != '-' && c != '£')	//remove all letter that aren't in alphabet
	{
		name = name.substr(1);
		c = name[0];
	}
	if (name[0] >= 'a' && name[0] <= 'z')
	{
		name[0] = name[0] - 'a' + 'A';
	}

	for (int i = 1; i < name.length(); i++)
	{
		c = name[i];
		if (c >= 'A' && c <= 'Z')
		{
			c = c - 'A' + 'a';
		}
	}
	c = name.back();
	while ((c < 'a' || c > 'z') && (c < 'A' || c > 'Z') && c != '-' && c != '£')	//remove all letter that aren't in alphabet
	{
		name = name.substr(0, name.length() - 1);
		c = name.back();
	}
}

void  Words::outputWord()
{
	cout << name << ": " << meaning << endl;
}

Words::Words(string nName)
{
	name = nName;
	meaning = "";
}

void Words::setName(string nName)
{
	name = nName;
}

void Words::setMeaning(string nMeaning)
{
	meaning = nMeaning;
}

string Words::getName()
{
	return name;
}