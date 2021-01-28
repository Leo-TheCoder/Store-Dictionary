#define _CRT_SECURE_NO_WARNINGS
#include "Words.h"
#include <chrono>
using namespace std::chrono;

struct Node
{
	Words key;
	Node* pNext;
};

void insertNode(Node*& pHead, Words data);

void split(Node* pHead, Node** left, Node** right)
{
	Node* slow = pHead;
	Node* fast = pHead->pNext;
	while (fast != NULL)
	{
		fast = fast->pNext;
		if (fast != NULL) {
			slow = slow->pNext;
			fast = fast->pNext;
		}
	}
	*left = pHead;
	*right = slow->pNext;
	slow->pNext = NULL;
}

Node* merge(Node* a, Node* b)
{
	Node* result = NULL;

	if (a == NULL) {
		return b;
	}
	else if (b == NULL) {
		return a;
	}

	if (a->key.getName() <= b->key.getName()) {
		result = a;
		result->pNext = merge(a->pNext, b);
	}
	else {
		result = b;
		result->pNext = merge(a, b->pNext);
	}
	return result;
}

void mergeSort(Node** dictionary)
{
	Node* pHead = *dictionary;
	Node* a;
	Node* b;
	if (pHead == NULL || pHead->pNext == NULL) {
		return;
	}
	split(pHead, &a, &b);
	mergeSort(&a);
	mergeSort(&b);
	*dictionary = merge(a, b);
}

void readFile(const char* str, Node*& dictionary)
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
			insertNode(dictionary, s);
		}
	}
	cin.clear();
	cin.ignore();
	freopen("CON", "rt", stdin);
}

Node* createNewNode(Words newWord)
{
	Node* s = new Node;
	s->key = newWord;
	s->pNext = NULL;
	return s;
}

void insertNode(Node*& pHead, Words data)
{
	if (pHead == NULL)
	{
		pHead = createNewNode(data);
	}
	else
	{
		Node* s = createNewNode(data);
		s->pNext = pHead;
		pHead = s;
	}
}

Node* lookUp(Node* pHead, string name)
{
	Node* cur = pHead;
	while (cur != NULL)
	{
		if (name == cur->key.getName()) {
			return cur;
		}
		cur = cur->pNext;
	}
	return NULL;
}

bool removeNode(Node*& pHead, Words data)
{
	if (pHead == NULL) return false;
	Node* s = lookUp(pHead, data.getName());
	if (s == NULL) {
		return false;
	}
	else
	{
		Node* temp = s->pNext;
		s->key = temp->key;
		s->pNext = temp->pNext;
		delete temp;
		return true;
	}
}

bool modifyWord(Node*& pHead, string name)
{
	Node* s = lookUp(pHead, name);
	if (s == NULL) return false;
	s->key.modifyMeaning();
	return true;
}

int doTask(Node*& dictionary)
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
		insertNode(dictionary,s);
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
			result->key.outputWord();
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


void writeFile(const char* str, Node* dictionary)
{
	freopen(str, "wt", stdout);
	Node* cur = dictionary;
	for (cur = dictionary; cur != NULL; cur = cur->pNext)
	{
		cout << cur->key.getName() << "  : " << cur->key.getMeaning() << endl << endl;
	}
	cin.clear();
	freopen("CON", "wt", stdout);
}

int countNode(Node* pHead)
{
	Node* cur = pHead;
	int count = 0;
	for (cur = pHead; cur != NULL; cur = cur->pNext)
	{
		count++;
	}
	return count;
}

int main()
{
	Node* dictionary = NULL;
	cout << "Reading file ... ";
	auto start = high_resolution_clock::now();
	readFile("Oxford English Dictionary.txt", dictionary);

	cin.clear();
	cout << "Done" << endl;
	auto stop = high_resolution_clock::now();
	auto duration = duration_cast<microseconds>(stop - start);
	//mergeSort(&dictionary);
	cout << "This function takes: " << duration.count() << " microseconds" << endl;
	int choice = 1;
	cout << "Size of dictionary: " << countNode(dictionary) << " words" << endl;
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