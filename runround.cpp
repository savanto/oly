/*
ID: washirv1
PROG: runround
LANG: C++
*/

#include <iostream>
#include <fstream>
using namespace std;

#define INFILE "runround.in"
#define OUTFILE "runround.out"

bool runround(int num[], int n)
{
	bool uniq[9] = { false };
	bool visit[9] = { false };
	int i, d;
	for (i = 0, d = 0; i < n; ++i, d = (num[d] + d) % n)
	{
		if (num[d] == 0)
			return false;
		if (visit[d])
			return false;
		if (uniq[num[d]-1])
			return false;

		visit[d] = true;
		uniq[num[d]-1] = true;
	}
	if (d != 0)
		return false;
	for (i = 0; i < n; ++i)
		if (! visit[i])
			return false;
	return true;
}

void split(int num[], int & n, int M)
{
	if (M == 0)
		return;
	split(num, n, M / 10);
	num[n++] = M % 10;
}

int main()
{
	// 81362
	ifstream fin(INFILE);
	int M;
	fin >> M;
	fin.close();

	int num[9], n = 0;
	split(num, n, ++M);
	while (! runround(num, n))
	{
		n = 0;
		split(num, n, ++M);
	}

	ofstream fout(OUTFILE);
	for (int i = 0; i < n; ++i)
		fout << num[i];
	fout << endl;
	fout.close();
	return 0;
}
