#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include "Words.h"
#include <chrono>
using namespace std;
using namespace std::chrono;


struct AVL_Word
{
	Words data;
	int bal;
	AVL_Word* pLeft;
	AVL_Word* pRight;
	AVL_Word* pNext;
};

AVL_Word* createNode(string strName, string strMeaning)
{
	AVL_Word* s = new AVL_Word;
	if (s == NULL) return NULL;
	s->data.setName(strName);
	s->data.setMeaning(strMeaning);
	s->bal = 0;
	s->pLeft = s->pRight = NULL;
	s->pNext = NULL;
	return s;
}

void leftRotate(AVL_Word*& p)
{
	AVL_Word* q = p->pRight;
	p->pRight = q->pLeft;
	q->pLeft = p;
	p = q;
}

void rightRotate(AVL_Word*& p)
{
	AVL_Word* q = p->pLeft;
	p->pLeft = q->pRight;
	q->pRight = p;
	p = q;
}

void leftBalance(AVL_Word*& p)
{
	switch (p->pLeft->bal)
	{
	case -1:
		rightRotate(p);
		p->bal = 0;
		p->pRight->bal = 0;
		break;
	case 1:
		leftRotate(p->pLeft);
		rightRotate(p);
		switch (p->bal)
		{
		case 0:
			p->pLeft->bal = 0;
			p->pRight->bal = 0;
			break;
		case -1:
			p->pLeft->bal = 0;
			p->pRight->bal = 1;
			break;
		case 1:
			p->pLeft->bal = -1;
			p->pRight->bal = 0;
			break;
		}
		p->bal = 0;
		break;
	}
}

void rightBalance(AVL_Word*& p)
{
	switch (p->pRight->bal)
	{
	case 1:
		leftRotate(p);
		p->bal = 0;
		p->pLeft->bal = 0;
		break;
	case -1:
		rightRotate(p->pRight);
		leftRotate(p);
		switch (p->bal)
		{
		case 0:
			p->pLeft->bal = 0;
			p->pRight->bal = 0;
			break;
		case -1:
			p->pLeft->bal = -1;
			p->pRight->bal = 0;
			break;
		case 1:
			p->pLeft->bal = 0;
			p->pRight->bal = 1;
			break;
		}
		p->bal = 0;
		break;
	}
}

int insertNode(AVL_Word*& tree, string newName, string newMeaning)
{
	int result;
	if (tree == NULL)
	{
		tree = createNode(newName, newMeaning);
		if (tree == NULL) return -1;
		return 2;
	}
	else
	{
		if (tree->data.getName() == newName)
		{
			AVL_Word* cur = tree;
			while (cur->pNext != NULL) {
				cur = cur->pNext;
			}
			cur->pNext = createNode(newName, newMeaning);
			return 0;
		}
		else if (tree->data.getName() > newName)
		{
			result = insertNode(tree->pLeft, newName, newMeaning);
			if (result < 2) return result;

			switch (tree->bal)
			{
			case 0:
				tree->bal = -1;
				return 2;
			case -1:
				leftBalance(tree);
				return 1;
			case 1:
				tree->bal = 0;
				return 1;
			}
		}
		else
		{
			result = insertNode(tree->pRight, newName, newMeaning);
			if (result < 2) return result;

			switch (tree->bal)
			{
			case 0:
				tree->bal = 1;
				return 2;
			case -1:
				tree->bal = 0;
				return 1;
			case 1:
				rightBalance(tree);
				return 1;
			}
		}
	}
}

void traverse(AVL_Word* tree)
{
	if (tree != NULL)
	{
		AVL_Word* cur = tree;
		while (cur != NULL) {
			cout << cur->data.getName() << "  : " << cur->data.getMeaning() << endl << endl;
			cur = cur->pNext;
		}
		traverse(tree->pLeft);
		traverse(tree->pRight);
	}
}

void removeAll(AVL_Word*& tree)
{
	if (tree != NULL)
	{
		removeAll(tree->pLeft);
		removeAll(tree->pRight);
		delete(tree);
	}
}

bool readingWord(string& name, string& meaning, string temp)
{
	size_t pos;
	pos = temp.find(":");
	if (pos != string::npos)
	{
		name = temp.substr(0, pos);
		meaning = temp.substr(pos + 1);
		return true;
	}
	else
	{
		name = meaning = "";
		return false;
	}
}

AVL_Word* lookUp(AVL_Word*& pTree, string str)
{
	if (pTree == NULL) {
		return NULL;
	}
	else
	{
		if (str > pTree->data.getName())
		{
			return lookUp(pTree->pRight, str);
		}
		else if (str < pTree->data.getName())
		{
			return lookUp(pTree->pLeft, str);
		}
		else
		{
			return pTree;
		}
	}
}

void searchStandFor(AVL_Word*& tree, AVL_Word*& p)
{
	if (tree->pRight != NULL)
	{
		searchStandFor(tree->pRight, p);
	}
	else
	{
		p->data.setName(tree->data.getName());
		p->data.setMeaning(tree->data.getMeaning());
		p = tree;
		tree = tree->pLeft;
	}
}

int getHeight(AVL_Word* tree)
{
	if (tree == NULL) {
		return 0;
	}
	int hR, hL;
	hL = getHeight(tree->pLeft);
	hR = getHeight(tree->pRight);
	if (hL > hR) {
		return 1 + hL;
	}
	return 1 + hR;
}

bool removeNode(AVL_Word*& pTree, string key)
{
	AVL_Word* p;
	if (pTree == NULL)
	{
		cout << "There is no word like that in dictionary" << endl;
		return false;
	}
	else
	{
		bool flag = false;
		if (pTree->data.getName() > key)
		{
			return removeNode(pTree->pLeft, key);
		}
		else if (pTree->data.getName() < key)
		{
			return removeNode(pTree->pRight, key);
		}
		else
		{
			AVL_Word* cur = pTree;
			int i = 1;
			while ((cur) != NULL) {
				cout << i << ". " << (cur)->data.getName() << ": " << (cur)->data.getMeaning() << endl;
				i++;
				cur = (cur)->pNext;
			}
			int all = i;
			if (all > 1) {
				if (i > 1) {
					cout << "Choose which word you want to remove: ";
					cin >> i;
					getchar();
				}
				if (all < i || i < 1) {
					cout << "Something went wrong!" << endl;
					return false;
				}
				else if (i > 1) {
					int count = 1;
					cur = pTree;
					while (cur->pNext != NULL && count + 1 < i) {
						cur = (cur)->pNext;
						count++;
					}
					if ((cur)->pNext != NULL) {
						AVL_Word* temp = cur->pNext;
						cur->pNext = cur->pNext->pNext;
						delete temp;
					}	
					return true;
				}
				else {
					pTree->data = pTree->pNext->data;
					pTree->pNext = pTree->pNext->pNext;
					delete pTree->pNext;
					return true;
				}
			}
			else {
				p = pTree;
				if (pTree->pLeft == NULL) {
					pTree = p->pRight;
				}
				else if (pTree->pRight == NULL) {
					pTree = p->pLeft;
				}
				else {
					searchStandFor(pTree->pLeft, p);
					flag = true;
				}
				delete(p);
			}
		}

		if (flag) {
			int balance = getHeight(pTree->pLeft) - getHeight(pTree->pRight);
			if (balance < -1)
			{
				leftBalance(pTree);
			}
			else if (balance > 1)
			{
				rightBalance(pTree);
			}
		}
		return true;
	}
}

void readFile(const char* str, AVL_Word*& dictionary)
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
			insertNode(dictionary, s.getName(), s.getMeaning());
		}
	}
	cin.clear();
	cin.ignore();
	freopen("CON", "rt", stdin);
}

void showNLR(AVL_Word* dictionary)
{
	if (dictionary != NULL) {
		cout << dictionary->data.getName() << "  : " << dictionary->data.getMeaning() << endl << endl;
		showNLR(dictionary->pLeft);
		showNLR(dictionary->pRight);
	}
}


void writeFile(const char* str, AVL_Word* dictionary)
{
	freopen(str, "wt", stdout);
	traverse(dictionary);
	cin.clear();
	freopen("CON", "wt", stdout);
}

bool modifyWord(AVL_Word*& pHead, string name)
{
	AVL_Word* s = lookUp(pHead, name);
	if (s == NULL) return false;
	s->data.modifyMeaning();
	return true;
}

void countNode(AVL_Word* pHead, int& count)
{
	if (pHead == NULL) {
		return;
	}
	AVL_Word* cur = pHead;
	while (cur != NULL) {
		count++;
		cur = cur->pNext;
	}
	countNode(pHead->pLeft, count);
	countNode(pHead->pRight, count);
}


int doTask(AVL_Word*& dictionary)
{
	int i;
	Words s;
	string name;
	Words temp;
	bool flag = false;
	AVL_Word* result;
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
	auto duration = duration_cast<microseconds> (stop - start);
	switch (choice)
	{
	case 1:
		s.inputWord();
		s.standardize();
		start = high_resolution_clock::now();
		insertNode(dictionary, s.getName(), s.getMeaning());
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
			for (AVL_Word* cur = result; cur != NULL; cur = cur->pNext) {
				cout << i << ". ";
				cur->data.outputWord();
				i++;
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
		flag = removeNode(dictionary, name);
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

int main()
{
	AVL_Word* dictionary = NULL;
	cout << "Reading file ... ";
	auto start = high_resolution_clock::now();
	readFile("Oxford English Dictionary.txt", dictionary);
	auto stop = high_resolution_clock::now();
	auto duration = duration_cast<microseconds>(stop - start);
	cin.clear();
	cout << "Done" << endl;
	cout << "This function takes: " << duration.count() << " microseconds" << endl;
	cout << "Tree's height = " << getHeight(dictionary) << endl;
	int count = 0;
	countNode(dictionary, count);
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