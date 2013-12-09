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

int main()
{
	ifstream fin(INFILE);

	fin.close();

	ofstream fout(OUTFILE);

	fout.close();
	return 0;
}
