/*
ID: washirv1
PROG: prefix
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

#define INFILE "prefix.in"
#define OUTFILE "prefix.out"

int main()
{
	ifstream fin(INFILE);
	vector<string> primitives;
	string p;
	fin >> p;
	while (p != ".")
	{
		primitives.push_back(p);
		fin >> p;
	}
	string sequence = "";
	while (fin >> p)
		sequence += p;
	fin.close();

	for (int i = 0; i < primitives.size(); ++i)
		cout << primitives[i] << endl;
	cout << sequence << endl;

	ofstream fout(OUTFILE);

	fout.close();
	return 0;
}
