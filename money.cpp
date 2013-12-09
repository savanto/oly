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

int main()
{
	ifstream fin(INFILE);
	int V, N;
	fin >> V >> N;
	int coins[N];
	for (int i = 0; i < V; ++i)
		fin >> coins[i];
	fin.close();

	unsigned long long ways[N+1];
	ways[0] = 1;
	for (int i = 1; i <= N; ++i)
		ways[i] = 0;
	for (int i = 0; i < V; ++i)
		for (int j = coins[i]; j <= N; ++j)
			ways[j] += ways[j - coins[i]];

	ofstream fout(OUTFILE);
	fout << ways[N] << endl;
	fout.close();
	return 0;
}
