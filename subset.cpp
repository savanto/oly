/*
ID: washirv1
PROG: subset
LANG: C++
*/

#include <iostream>
#include <fstream>
using namespace std;

#define INFILE "subset.in"
#define OUTFILE "subset.out"

int main()
{
	ifstream fin(INFILE);
	int N;
	fin >> N;
	fin.close();
	ofstream fout(OUTFILE);

	int W = 0;
	for (int i = 1; i <= N; ++i)
		W += i;

	// Sum must be even, else it is not possible to make subsets of equal sums
	if (W % 2 != 0)
		fout << 0 << endl;
	else	// Variation of the Knapsack problem
	{
		W /= 2;	// this is the capacity of the knapsack
		int s[N+1][W+1], i, j;
		for (i = 0, j = 0; j <= W; ++j)
			s[i][j] = 0;
		for (i = 1; i <= N; ++i)
		{
			s[i][0] = 0;
			for (j = 1; j <= W; ++j)
			{
				if (s[i-1][j])
					s[i][j] = 1;
				else if (s[i-1][j-i])
					s[i][j] = 1;
				else
					s[i][j] = 0;
			}
		}

		for (i = 0; i <= N; ++i)
		{
			for (j = 0; j <= W; ++j)
				cout << s[i][j] << ' ';
			cout << endl;
		}
	}





	fout.close();
	return 0;
}
