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

int count(int **v, int i, int w)
{
	if (w == 0 || w == i * (i + 1) / 2)
		return 1;
	if (w < 0 || i < 1 || w > i * (i + 1) / 2)
		return 0;
	if (v[i][w])
		return v[i][w];
	int c = count(v, w, i - 1);
	c += count(v, w - i, i - 1);
	v[i][w] = c;
	return c;
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
		W /= 2;	// 1/2 of total sequence sum is the capacity of the knapsack
		int v[N+1][W+1], i, w, s = 0;
		for (i = 0; i <= N; ++i)
			for (w = 0; w <= W; ++w)
				v[i][w] = 0;
/*
		for (i = 1; i <= N; ++i)
		{
			for (w = 0; w <= W; ++w)
			{
				if (i <= w)
				{
					if (v[i-1][w])
						++v[i][w];
					if (v[i-1][w-i])
						++v[i][w];
				}
				else
					++v[i][w];
			}
		}
*/
		cout << count(v, N, W) << endl;
		for (i = 1; i <= N; ++i)
		{
			for (w = 0; w <= W; ++w)
				cout << v[i][w] << ' ';
			cout << endl;
		}
	}





	fout.close();
	return 0;
}
