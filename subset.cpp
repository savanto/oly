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

	int W = N * (N + 1) / 2;
	if (W % 2 != 0)
		fout << 0 << endl;
	else
	{
		W /= 2;
		long long s[W * W];
		s[0] = 1;
		for (int i = 1; i < W * W; ++i)
			s[i] = 0;
		for (int i = 1; i <= N; ++i)
			for (int w = W - i; w >= 0; --w)
				s[w + i] += s[w];
		fout << s[W] / 2 << endl;
	}

	fout.close();
	return 0;
}
