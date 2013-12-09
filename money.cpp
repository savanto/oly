/*
ID: washirv1
PROG: money
LANG: C++
*/

#include <iostream>
#include <fstream>
using namespace std;

#define INFILE "money.in"
#define OUTFILE "money.out"

void make_money(int N, int V, int system[], unsigned long long& ways)
{
	if (N == 0)
	{
		++ways;
		return;
	}
	if (N < 0)
		return;

	for (int i = 0; i < V; ++i)
		make_money(N - system[i], V, system, ways);
}

int main()
{
	ifstream fin(INFILE);
	int V, N;
	fin >> V >> N;
	int system[N];
	for (int i = 0; i < V; ++i)
		fin >> system[i];
	fin.close();

	unsigned long long ways = 0;
	make_money(N, V, system, ways);
/*
	unsigned long long ways[N * N];
	ways[0] = 1;
	for (int i = 1; i < N * N; ++i)
		ways[i] = 0;
	for (int i = 1; i <= 5; ++i)
		for (int w = N - i; w >= 0; --w)
			ways[w + i] += ways[w];
*/
	ofstream fout(OUTFILE);
	cout << ways << endl;
	fout.close();
	return 0;
}

/*
long long s[W * W];
		s[0] = 1;
		for (int i = 1; i < W * W; ++i)
			s[i] = 0;
		for (int i = 1; i <= N; ++i)
			for (int w = W - i; w >= 0; --w)
				s[w + i] += s[w];
*/
