/*
ID: washirv1
PROG: sort3
LANG: C++
*/

#include <fstream>
#include <iostream>
using namespace std;

#define INFILE "sort3.in"
#define OUTFILE "sort3.out"

void swap(int recs[], int i, int j)
{
	int t = recs[i];
	recs[i] = recs[j];
	recs[j] = t;
}

int main()
{
	ifstream fin(INFILE);
	int N, n12 = 0, n21 = 0, n13 = 0, n31 = 0, n23 = 0, n32 = 0;
	fin >> N;
	int recs[N], ones = 0, twos = 0, threes = 0;
	for (int i = 0; i < N; ++i)
	{
		fin >> recs[i];
		switch (recs[i])
		{
			case 1: ++ones; break;
			case 2: ++twos; break;
			case 3: ++threes; break;
		}
	}
	fin.close();

	for (int i = 0; i < ones; ++i)
	{
		if (recs[i] == 2)
			++n21;
		else if (recs[i] == 3)
			++n31;
	}

	for (int i = ones; i < ones + twos; ++i)
	{
		if (recs[i] == 1)
			++n12;
		else if (recs[i] == 3)
			++n32;
	}

	for (int i = ones + twos; i < N; ++i)
	{
		if (recs[i] == 1)
			++n13;
		else if (recs[i] == 2)
			++n23;
	}

	ofstream fout(OUTFILE);
/*
	fout << "1<->2 " << n12 << endl;
	fout << "1<->3 " << n13 << endl;
	fout << "2<->1 " << n21 << endl;
	fout << "2<->3 " << n23 << endl;
	fout << "3<->1 " << n31 << endl;
	fout << "3<->2 " << n32 << endl;
*/
	int a = n12 + n13 + n23;
	int b = n21 + n31 + n32;

	fout << (a > b ? a : b) << endl;
	fout.close();
	return 0;
}
