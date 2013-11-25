/*
ID: washirv1
PROG: holstein
LANG: C++
*/

#include <iostream>
#include <fstream>
using namespace std;

#define INFILE "holstein.in"
#define OUTFILE "holstein.out"

struct Node
{
	int scoops;
	Node * next;
	Node(int s = 0, Node * n = NULL) : scoops(s), next(n) {}
};

struct Queue
{
	Node * first;
	Node * last;
	Queue() : first(NULL), last(NULL) {}
	bool empty() { return first == NULL; }
	void push(int s)
	{
		if (last == NULL)
			first = last = new Node(s);
		else
			last = last->next = new Node(s);
	}
	int pop()
	{
		Node * n = first;
		int s = n->scoops;
		first = first->next;
		delete n;
		return s;
	}
};

int main()
{
	ifstream fin(INFILE);
	int V, G, v, g;
	fin >> V;
	int reqs[V];
	for (v = 0; v < V; ++v)
		fin >> reqs[v];
	fin >> G;
	int feeds[G][V];
	for (g = 0; g < G; ++g)
		for (v = 0; v < V; ++v)
			fin >> feeds[g][v];
	fin.close();

	Queue q;
	for (g = 0; g < G; ++g)
		q.push(1 << g);

	ofstream fout(OUTFILE);
	while (! q.empty())
	{
		int s = q.pop();
		int test[V];
		for (v = 0; v < V; ++v)
			test[v] = 0;
		int bit, n = 0;
		for (g = 0, bit = 1; g < G; ++g, bit <<= 1)
			if (bit & s)
			{
				for (v = 0; v < V; ++v)
					test[v] += feeds[g][v];
				++n;
			}
		bool pass = true;
		for (v = 0; v < V; ++v)
			if (test[v] < reqs[v])
			{
				pass = false;
				break;
			}
		if (pass)
		{
			fout << n << ' ';
			for (g = 0, bit = 1; g < G; ++g, bit <<= 1)
				if (bit & s)
				{
					fout << g+1;
					--n;
					if (n != 0)
						fout << ' ';
				}
			fout << endl;
			fout.close();
			return 0;
		}
		else
		{
//			for (g = 0, bit = 1; g < G; ++g, bit <<= 1)
//				if (bit & s)
//					cout << g+1 << ' ';
//			cout << endl;

			for (bit = 1 << G, g = G-1; ! (bit & s); bit >>= 1, --g);
			for (g = g + 2, bit = (bit == 0 ? 1 : bit << 1); g < G; ++g, bit <<= 1)
				q.push(s | bit);
		}
	}

	return 0;
}
