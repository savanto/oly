/*
ID: washirv1
PROG: concom
LANG: C++
*/

#include <iostream>
#include <fstream>
using namespace std;

#define INFILE "concom.in"
#define OUTFILE "concom.out"

#define N 100

int main()
{
	ifstream fin(INFILE);
	int n;
	fin >> n;
	int control[N][N], p, c;
	for (p = 0; p < N; ++p)
		for (c = 0; c < N; ++c)
			control[p][c] = 0;
	for (int i = 0; i < n; ++i)
	{
		int stake;
		fin >> p >> c >> stake;
		control[p-1][c-1] = stake;
	}
	fin.close();

	for (p = 0; p < N; ++p)
	{
		for (c = 0; c < N; ++c)
		{
			for (int cp = 0; cp < N; ++cp)
			{
				if (control[p][cp] > 50)
					control[p][c] += control[cp][c];
			}
		}
	}

	ofstream fout(OUTFILE);

	for (p = 0; p < N; ++p)
		for (c = 0; c < N; ++c)
			if (p != c)
				if (control[p][c] > 50)
					fout << p+1 << ' ' << c+1 << endl;

	fout.close();
	return 0;
}
