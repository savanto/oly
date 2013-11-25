/*
ID: washirv1
PROG: PROGRAM
LANG: C++
*/

#include <iostream>
#include <fstream>
using namespace std;

#define INFILE "PROGRAM.in"
#define OUTFILE "PROGRAM.out"

int main()
{
	ifstream fin(INFILE);

	fin.close();

	ofstream fout(OUTFILE);

	fout.close();
	return 0;
}
