/*
ID: washirv1
PROG: sprime
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

#define INFILE "sprime.in"
#define OUTFILE "sprime.out"

struct ListNode
{
	unsigned long int val;
	ListNode *next;
	ListNode *prev;
	ListNode(unsigned long int v) : val(v), next(NULL), prev(NULL) {}
	ListNode(unsigned long int v, ListNode *p) : val(v), next(NULL), prev(p) {}
};

struct List
{
	ListNode *first;
	ListNode *last;
	List() : first(NULL), last(NULL) {}
	void push_back(unsigned long int v)
	{
		if (first == NULL)
		{
			first = new ListNode(v);
			last = first;
		}
		else
		{
			last->next = new ListNode(v, last);
			last = last->next;
		}
	}
};

bool isPrime(unsigned long int n, List *prime)
{
	if (n <= 1)
		return false;
	ListNode *iterator = prime->first;
	while (iterator->next != NULL && iterator->val * iterator->val < n)
	{
		if (n == iterator->val)
			return true;
		if (n % iterator->val == 0)
			return false;
		iterator = iterator->next;
	}
	if (n == iterator->val)
		return true;
	if (n % iterator->val == 0)
		return false;
	prime->push_back(n);
	return true;
}

bool isSuperprime(unsigned long int n, List *prime, List *super)
{
	if (! isPrime(n, prime))
		return false;
	ListNode *iterator = super->last;
	while (iterator->prev != NULL && iterator->val >= n / 10)
	{
		if (iterator->val == n / 10)
		{
			super->push_back(n);
			return true;
		}
		iterator = iterator->prev;
	}
	if (iterator->val == n / 10)
	{
		super->push_back(n);
		return true;
	}
	return false;
}

int main()
{
	int n, min = 1, max = 9, i;
	ifstream fin(INFILE);
	fin >> n;
	fin.close();

	for (i = 1; i < n; i++)
	{
		min *= 10;
		max = max * 10 + 9;
	}

	List *prime = new List(), *super = new List();
	prime->push_back(2);
	super->push_back(2);
	for (i = 3; i <= 7; i+=2)
	{
		prime->push_back(i);
		super->push_back(i);
	}

	ofstream fout(OUTFILE);

	if (n == 1)
	{
		for (i = 2; i < 10; i++)
			if (isPrime(i, prime))
				fout << i << endl;
		return 0;
	}

	for (i = 11; i < min; i+=2)
		isSuperprime(i, prime, super);


	cout << "done collecting primes." << endl;

	for (min++; min <= max; min+=2)
	{
		if (isSuperprime(min, prime, super))
			fout << min << endl;
	}

	fout.close();
	return 0;
}
