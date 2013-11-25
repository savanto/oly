/*
ID: washirv1
PROG: sprime
LANG: C++
*/

#include <fstream>
using namespace std;

#define INFILE "sprime.in"
#define OUTFILE "sprime.out"

struct Node
{
	int val;
	Node * next;
	Node(int v) : val(v), next(NULL) {}
};

void insert(Node * primes, int v)
{
	// Traverse primes so far, check primeness.
	// Insert only if prime.
	Node * node = primes;
	while (node->next != NULL)
	{
		if (v % node->val == 0)
			return;
		node = node->next;
	}
	if (v % node->val == 0)
		return;
	node->next = new Node(v);
}

bool prime(Node * primes, int v)
{
	Node * node = primes;
	while (node->next != NULL)
	{
		if (v % node->val == 0)
		{
			if (v == node->val)
				return true;
			return false;
		}
		node = node->next;
	}
	if (v % node->val == 0)
	{
		if (v == node->val)
			return true;
		return false;
	}
	return true;
}

const int T[] = {1, 3, 7, 9};
void superprime(ofstream & fout, Node * primes, int start, int level)
{
	if (level == 0)
	{
		fout << start << endl;
		return;
	}
	for (int i = 0, test; i < 4; i++)
	{
		test = start * 10 + T[i];
		if (prime(primes, test))
		{
			superprime(fout, primes, test, level - 1);
		}
	}
}

int main()
{
	int n, p = 1, i;
	ifstream fin(INFILE);
	fin >> n;
	fin.close();

	ofstream fout(OUTFILE);
	if (n == 1)
	{
		fout << 2 << endl << 3 << endl << 5 << endl << 7 << endl;
		fout.close();
		return 0;
	}

	// Primes need be only n/2 digits long
	for (i = 0; i < (n + 1) / 2; i++)
		p *= 10;
	
	// Generate primes of length 1 <= p < n/2
	Node * primes = new Node(2);
	for (i = 3; i < p; i+=2)
		insert(primes, i);

	// Generate superprimes of length n using primes as base
	for (i = 0; i < n - (n + 1) / 2; i++)
		p *= 10;
	superprime(fout, primes, 2, n - 1);
	superprime(fout, primes, 3, n - 1);
	superprime(fout, primes, 5, n - 1);
	superprime(fout, primes, 7, n - 1);
	fout.close();
	return 0;
}
