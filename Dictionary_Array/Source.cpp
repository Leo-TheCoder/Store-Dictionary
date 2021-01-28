#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <malloc.h>
#include <stdlib.h>
#include <vector>
#include <chrono>
#include "Words.h"
using namespace std;
using namespace std::chrono;


void swap(Words& x, Words& y)
{
	Words temp = x;
	x = y;
	y = temp;
}

void merge(vector<Words>& dictionary, int l, int m, int r)
{
	int i, j, k;
	int n1 = m - l + 1;
	int n2 = r - m;
	vector<Words> L, R;
	for (i = 0; i < n1; i++) {
		L.push_back(dictionary[l + i]);
	}
	for (j = 0; j < n2; j++) {
		R.push_back(dictionary[m + 1 + j]);
	}
	i = 0;
	j = 0;
	k = l;
	while (i < n1 && j < n2) {
		if (L[i].getName() <= R[j].getName())
		{
			dictionary[k] = L[i];
			i++;
		}
		else
		{
			dictionary[k] = R[j];
			j++;
		}
		k++;
	}
	while (i < n1) {
		dictionary[k] = L[i];
		i++;
		k++;
	}
	while (j < n2) {
		dictionary[k] = R[j];
		j++;
		k++;
	}
}

void mergeSort(vector<Words>& dictionary, int left, int right) {
	if (left < right)
	{
		int mid = left + (right - left) / 2;
		mergeSort(dictionary, left, mid);
		mergeSort(dictionary, mid + 1, right);

		merge(dictionary, left, mid, right);
	}
}

void readFile(const char *str, vector<Words>& dictionary)
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
			dictionary.push_back(s);
		}
	}
	
	cin.clear();
	cin.ignore();
	freopen("CON", "rt", stdin);
	cin.clear();
}

void insertWord(vector<Words>& dictionary)
{
	Words s;
	int i = 0;
	s.inputWord();
	s.standardize();
	auto start = high_resolution_clock::now();
	for (i = 0; i < dictionary.size() - 1; i++)
	{
		if (dictionary[i].getName() <= s.getName() && s.getName() < dictionary[i + 1].getName())
		{
			dictionary.insert(dictionary.begin() + i + 1, s);
			cout << "Inserted!" << endl;
			break;
		}
	}
	if (i == dictionary.size() - 1)
	{
		dictionary.insert(dictionary.begin() + i + 1, s);
		cout << "Inserted!" << endl;
	}
	auto stop = high_resolution_clock::now();
	auto duration = duration_cast<microseconds>(stop - start);
	cout << "This function takes: " << duration.count() << " microseconds" << endl;
}

int lookUp(vector<Words> dictionary, string name, vector<Words>& result)
{
	result.clear();
	bool flag = false;
	auto start = high_resolution_clock::now();
	for (int i = 0; i < dictionary.size(); i++)
	{
		if (dictionary[i].getName() == name)
		{
			Words temp = dictionary[i];
			result.push_back(temp);
			flag = true;
		}
		if (flag && dictionary[i].getName() != name)
		{
			auto stop = high_resolution_clock::now();
			auto duration = duration_cast<microseconds>(stop - start);
			cout << "This function takes: " << duration.count() << " microseconds" << endl;
			return i - result.size();
		}
	}
	auto stop = high_resolution_clock::now();
	auto duration = duration_cast<microseconds>(stop - start);
	cout << "This function takes: " << duration.count() << " microseconds" << endl;
	return -1;
}

void removeWord(vector<Words>& dictionary, string name)
{
	vector<Words> result;
	int iterator = lookUp(dictionary, name, result);
	if (iterator >= 0)
	{
		cout << "There is " << result.size() << " " << name << " in this dictionary:" << endl;
		for (int i = 0; i < result.size(); i++)
		{
			cout << i + 1 << ". ";
			result[i].outputWord();
		}
		if (result.size() > 1)
		{
			cout << "Choose one word to remove (use number): ";
			int choice;
			cin >> choice;
			getchar();
			auto start = high_resolution_clock::now();
			if (choice <= result.size() && choice >= 0)
			{
				choice--;
				dictionary.erase(dictionary.begin() + iterator + choice);
				cout << "Removed!" << endl;
				auto stop = high_resolution_clock::now();
				auto duration = duration_cast<microseconds>(stop - start);
				cout << "This function takes: " << duration.count() << " microseconds" << endl;
			}
			else
			{
				cout << "Something went wrong :)))" << endl;
			}
		}
		else
		{
			cout << "Do you want to remove this word (y/n)? ";
			char c;
			cin >> c;
			getchar();
			auto start = high_resolution_clock::now();
			if (c == 'Y' || c == 'y') {
				dictionary.erase(dictionary.begin() + iterator);
			}
			cout << "Removed!" << endl;
			auto stop = high_resolution_clock::now();
			auto duration = duration_cast<microseconds>(stop - start);
			cout << "This function takes: " << duration.count() << " microseconds" << endl;
		}
	}
	else {
		cout << "There is no word like that in dictionary!" << endl;
	}
}

void modifyWord(vector<Words>& dictionary, string name)
{
	vector<Words> result;
	int iterator = lookUp(dictionary, name, result);
	if (iterator >= 0)
	{
		cout << "There is " << result.size() << " " << name << " in this dictionary:" << endl;
		for (int i = 0; i < result.size(); i++)
		{
			cout << i + 1 << ". ";
			result[i].outputWord();
		}
		if (result.size() > 1)
		{
			cout << "Choose one word to modify (use number): ";
			int choice;
			cin >> choice;
			getchar();
			auto start = high_resolution_clock::now();
			if (choice <= result.size() && choice >= 0)
			{
				choice--;
				dictionary[iterator + choice].modifyMeaning();
				cout << "Modified!" << endl;
				auto stop = high_resolution_clock::now();
				auto duration = duration_cast<microseconds>(stop - start);
				cout << "This function takes: " << duration.count() << " microseconds" << endl;
			}
			else
			{
				cout << "Something went wrong :)))" << endl;
			}
		}
		else
		{
			cout << "Do you want to modify this word (y/n)? ";
			char c;
			cin >> c;
			getchar();
			auto start = high_resolution_clock::now();
			if (c == 'Y' || c == 'y') {
				dictionary[iterator].modifyMeaning();
			}
			cout << "Modified!" << endl;
			auto stop = high_resolution_clock::now();
			auto duration = duration_cast<microseconds>(stop - start);
			cout << "This function takes: " << duration.count() << " microseconds" << endl;
		}
	}
	else {
		cout << "There is no word like that in dictionary!" << endl;
	}
}

int doTask(vector<Words>& dictionary)
{
	vector<Words> result;
	string name;
	Words temp;
	int i;
	cout << "1. Insert word" << endl;
	cout << "2. Look up word" << endl;
	cout << "3. Remove word" << endl;
	cout << "4. Modify word" << endl;
	cout << "5. Exit" << endl;
	int choice;
	cout << "Get your choice: ";
	cin >> choice;
	getchar();
	switch (choice)
	{
	case 1:
		insertWord(dictionary);
		break;
	case 2:
		cout << "Input your word: ";
		getline(cin, name);
		temp.setName(name);
		temp.standardize();
		name = temp.getName();
		i = lookUp(dictionary, name, result);
		if (i < 0)
		{
			cout << "There is no word like that in dictionary!" << endl;
		}
		else
		{
			for (int i = 0; i < result.size(); i++)
			{
				cout << i + 1 << ". ";
				result[i].outputWord();
			}
		}
		break;
	case 3:
		cout << "Input your word: ";
		getline(cin, name);
		temp.setName(name);
		temp.standardize();
		name = temp.getName();
		removeWord(dictionary, name);
		break;
	case 4:
		cout << "Input your word: ";
		getline(cin, name);
		temp.setName(name);
		temp.standardize();
		name = temp.getName();
		modifyWord(dictionary, name);
		break;
	default:
		break;
	}
	return choice;
}

void writeFile(vector<Words> dictionary, const char *str)
{
	freopen(str, "wt", stdout);
	for (int i = 0; i < dictionary.size(); i++)
	{
		cout << dictionary[i].getName() << "  " << dictionary[i].getMeaning() << endl << endl;
	}
	cin.clear();

	freopen("CON", "wt", stdout);

}

int main()
{
	vector<Words> dictionary;
	int n = 0;
	cout << "Reading file ... ";
	auto start = high_resolution_clock::now();
	readFile("Oxford English Dictionary.txt", dictionary);
	mergeSort(dictionary, 0, dictionary.size() - 1);
	auto stop = high_resolution_clock::now();
	cout << "Done" << endl;
	auto duration = duration_cast<microseconds> (stop - start);
	cout << "This function takes: " << duration.count() << " microseconds" << endl;
	cout << "Size of dictionary: " << dictionary.size() << " words" << endl;
	int choice = 1;
	while (choice >= 1 && choice <= 4)
	{
		cout << "--------------------------------" << endl;
		choice = doTask(dictionary);
		cout << "--------------------------------" << endl;
	}
	cout << "Writing file ... ";
	start = high_resolution_clock::now();
	writeFile(dictionary, "output.txt");
	stop = high_resolution_clock::now();
	duration = duration_cast<microseconds> (stop - start);
	cout << "Done" << endl;
	cout << "This function takes: " << duration.count() << " microseconds" << endl;

	return 0;
}