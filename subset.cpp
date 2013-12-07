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

int max(int a, int b)
{
	return (a > b ? a : b);
}

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
		int v[N+1][W+1], i, w, s = 0;
		for (w = 0; w <= W; ++w)
			v[0][w] = 0;
		for (i = 0; i <= N; ++i)
			v[i][0] = 0;
		for (w = 1; w <= W; ++w)
		{
			for (i = 0; i <= N; ++i)
			{
				if (i <= w)
				{
					if (i + v[i-1][w-i] >= v[i-1][w])
					{
						v[i][w] = i + v[i-1][w-i];
						cout << i + v[i-1][w-i] << ">=" <<v[i-1][w] << endl;
					}
					else
					{
						v[i][w] = v[i-1][w];
					}
				}
				else
				{
					v[i][w] = v[i-1][w];
				}
			}
		}

		for (i = 0; i <= N; ++i)
		{
			for (w = 0; w <= W; ++w)
				cout << v[i][w] << ' ';
			cout << endl;
		}
		cout << s << endl;
	}





	fout.close();
	return 0;
}
