/*
ID: washirv1
PROG: prefix
LANG: C++
*/

#include <iostream>
#include <fstream>
using namespace std;

#define INFILE "prefix.in"
#define OUTFILE "prefix.out"

int main()
{
	ifstream fin(INFILE);

	fin.close();

	ofstream fout(OUTFILE);

	fout.close();
	return 0;
}
