#pragma once
#include <malloc.h>
#include <iostream>
#include <string>
using namespace std;

class Words
{
private:
	string name;
	string meaning;
public:
	bool readWord(string sentence);
	void inputWord();
	void outputWord();
	void modifyMeaning();
	void standardize();
	string getName();
	string getMeaning();
	Words(string nName);
	void setName(string nName);
	Words(const Words&);
	Words();
	~Words();
};

