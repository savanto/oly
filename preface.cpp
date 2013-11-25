/*
ID: washirv1
PROG: preface
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

#define INFILE "preface.in"
#define OUTFILE "preface.out"
const int DECIMAL[]	= { 1000, 900, 500, 400, 100, 90, 50, 40, 10, 9,  5, 4, 1 };
const string ROMAN[]= { "M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I" };
//////////////////////	 0	   1	2	  3	   4	 5	  6		7	 8	   9	10	 11	   12
const int M = 13;

int main()
{
	ifstream fin(INFILE);
	int N;
	fin >> N;
	fin.close();

	int counts[M] = { 0 };
	for (int n = 1, d = n; n <= N; d = ++n)
	{
		for (int m = 0; d; ++m)
		{
			int r = d / DECIMAL[m];
			d -= r * DECIMAL[m];
			counts[m] += r;
		}
	}

	ofstream fout(OUTFILE);
	
	// I
	counts[12] += counts[9] + counts[11];
	if (counts[12] > 0)
		fout << ROMAN[12] << ' ' << counts[12] << endl;
	// V
	counts[10] += counts[11];
	if (counts[10] > 0)
		fout << ROMAN[10] << ' ' << counts[10] << endl;
	// X
	counts[8] += counts[5] + counts[7] + counts[9];
	if (counts[8] > 0)
		fout << ROMAN[8] << ' ' << counts[8] << endl;
	// L
	counts[6] += counts[7];
	if (counts[6] > 0)
		fout << ROMAN[6] << ' ' << counts[6] << endl;
	// C
	counts[4] += counts[1] + counts[3] + counts[5];
	if (counts[4] > 0)
		fout << ROMAN[4] << ' ' << counts[4] << endl;
	// D
	counts[2] += counts[3];
	if (counts[2] > 0)
		fout << ROMAN[2] << ' ' << counts[2] << endl;
	// M
	counts[0] += counts[1];
	if (counts[0] > 0)
		fout << ROMAN[0] << ' ' << counts[0] << endl;

	fout.close();
	return 0;
}
