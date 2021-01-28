#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include "Words.h"
#include <chrono>
using namespace std;
using namespace std::chrono;

#define SIZE_TABLE 2003

struct Node
{
	Words data;
	Node* pNext;
};

int hashingWord(string word)
{
	int len = word.length();
	int i = 0;

	unsigned long temp = 0;
	int sum = 0;
	for (i = 0; i < len; i++)
	{
		sum += (int)word[i];
		temp += (int)word[i] * pow(11, i);
	}
	return ((temp % sum) * len) % SIZE_TABLE;
}

Node* createNewNode(string nName, string nMeaning)
{
	Node* s = new Node;
	if (s == NULL) return NULL;
	s->data.setName(nName);
	s->data.setMeaning(nMeaning);
	s->pNext = NULL;
	return s;
}

void insertWord(Node* dictionary[], string name, string meaning)
{
	int pos = hashingWord(name);
	if (dictionary[pos] == NULL)
	{
		dictionary[pos] = createNewNode(name, meaning);
	}
	else
	{
		Node* s = createNewNode(name, meaning);
		s->pNext = dictionary[pos];
		dictionary[pos] = s;
	}
}

Node* lookUp(Node* dictionary[], string name)
{
	int pos = hashingWord(name);
	if (dictionary[pos] == NULL)
	{
		return NULL;
	}
	else
	{
		Node* cur = dictionary[pos];
		for (cur = dictionary[pos]; cur != NULL; cur = cur->pNext)
		{
			if (cur->data.getName() == name) {
				return cur;
			}
		}
		return NULL;
	}
}

bool removeWord(Node* dictionary[], string name)
{
	Node* s = lookUp(dictionary, name);
	if (s == NULL)
	{
		return false;
	}
	else {
		Node* temp = s->pNext;
		s->data = temp->data;
		s->pNext = temp->pNext;
		delete temp;
		return true;
	}
}

bool modifyWord(Node* dictionary[], string name)
{
	Node* s = lookUp(dictionary, name);
	if (s == NULL) return false;
	s->data.modifyMeaning();
	return true;
}

int doTask(Node* dictionary[])
{
	int i;
	Words s;
	string name;
	Words temp;
	bool flag = false;
	Node* result;
	cout << "1. Insert word" << endl;
	cout << "2. Look up word" << endl;
	cout << "3. Remove word" << endl;
	cout << "4. Modify word" << endl;
	cout << "5. Exit" << endl;
	int choice;
	cout << "Get your choice: ";
	cin >> choice;
	getchar();
	auto start = high_resolution_clock::now();
	auto stop = high_resolution_clock::now();
	auto duration = duration_cast<microseconds>(stop - start);
	switch (choice)
	{
	case 1:
		s.inputWord();
		s.standardize();
		start = high_resolution_clock::now();
		insertWord(dictionary, s.getName(), s.getMeaning());
		stop = high_resolution_clock::now();
		duration = duration_cast<microseconds>(stop - start);
		cout << "This function takes: " << duration.count() << " microseconds" << endl;
		break;
	case 2:
		cout << "Input your word: ";
		getline(cin, name);
		temp.setName(name);
		temp.standardize();
		name = temp.getName();
		start = high_resolution_clock::now();
		result = lookUp(dictionary, name);
		if (result == NULL)
		{
			cout << "There is no word like that in dictionary!" << endl;
		}
		else
		{
			int i = 1;
			for (Node* cur = result; cur != NULL; cur = cur->pNext) {
				if (cur->data.getName() == name) {
					cout << i << ". ";
					cur->data.outputWord();
					i++;
				}
			}
		}
		stop = high_resolution_clock::now();
		duration = duration_cast<microseconds>(stop - start);
		cout << "This function takes: " << duration.count() << " microseconds" << endl;
		break;
	case 3:
		cout << "Input your word: ";
		getline(cin, name);
		temp.setName(name);
		temp.standardize();
		name = temp.getName();
		start = high_resolution_clock::now();
		flag = removeWord(dictionary, name);
		if (flag)
		{
			cout << "Done!" << endl;
		}
		else {
			cout << "There is no word like that in dictionary!" << endl;
		}
		stop = high_resolution_clock::now();
		duration = duration_cast<microseconds>(stop - start);
		cout << "This function takes: " << duration.count() << " microseconds" << endl;
		break;
	case 4:
		cout << "Input your word: ";
		getline(cin, name);
		temp.setName(name);
		temp.standardize();
		name = temp.getName();
		start = high_resolution_clock::now();
		flag = modifyWord(dictionary, name);
		if (flag)
		{
			cout << "Done!" << endl;
		}
		else {
			cout << "There is no word like that in dictionary!" << endl;
		}
		stop = high_resolution_clock::now();
		duration = duration_cast<microseconds>(stop - start);
		cout << "This function takes: " << duration.count() << " microseconds" << endl;
		break;
	default:
		break;
	}
	return choice;
}

void readFile(const char* str, Node* dictionary[])
{
	freopen(str, "rt", stdin);
	string temp;
	while (!cin.eof())
	{
		getline(cin, temp);
		if (temp.length() <= 3) continue;
		Words s;
		bool read = s.readWord(temp);
		if (read)
		{
			s.standardize();
			insertWord(dictionary, s.getName(), s.getMeaning());
		}
	}
	cin.clear();
	cin.ignore();
	freopen("CON", "rt", stdin);
}

void writeFile(const char* str, Node* dictionary[])
{
	freopen(str, "wt", stdout);
	for (int i = 0; i < SIZE_TABLE; i++)
	{
		Node* cur = dictionary[i];
		while (cur != NULL)
		{
			cout << cur->data.getName() << "  : " << cur->data.getMeaning() << endl << endl;
			cur = cur->pNext;
		}
	}
	cin.clear();
	freopen("CON", "wt", stdout);
}

int countNode(Node* dictionary[])
{
	int count = 0;
	for (int i = 0; i < SIZE_TABLE; i++)
	{
		for (Node* cur = dictionary[i]; cur != NULL; cur = cur->pNext)
		{
			count++;
		}
	}
	return count;
}


int main()
{
	Node* dictionary[SIZE_TABLE] = { NULL };
	cout << "Reading file ... ";
	auto start = high_resolution_clock::now();
	readFile("Oxford English Dictionary.txt", dictionary);
	auto stop = high_resolution_clock::now();
	cin.clear();
	cout << "Done" << endl;
	auto duration = duration_cast<microseconds> (stop - start);
	cout << "This function takes: " << duration.count() << " microseconds" << endl;
	int count = countNode(dictionary);
	cout << "Size of dictionary: " << count << " words" << endl;
	int choice = 1;
	while (choice >= 1 && choice <= 4)
	{
		cout << "--------------------------------" << endl;
		choice = doTask(dictionary);
		cout << "--------------------------------" << endl;
	}
	cout << "Writing file ... ";
	start = high_resolution_clock::now();
	writeFile("output.txt", dictionary);
	cout << "Done" << endl;
	stop = high_resolution_clock::now();
	duration = duration_cast<microseconds>(stop - start);
	cout << "This function takes: " << duration.count() << " microseconds" << endl;
	return 0;
}