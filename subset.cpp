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

	fout.close();
	return 0;
}
