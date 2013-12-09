/*
ID: washirv1
PROG: prefix
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
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

	sort(primitives.begin(), primitives.end());
	int k = 0, s = sequence.length();
	while (k < s)
	{
		int i;
		for (i = primitives.size() - 1; i >= 0; --i)
		{
			int p = primitives[i].length();
			if (primitives[i] == sequence.substr(k, p))
			{
				k += p;
				break;
			}
		}
		if (i < 0)
			break;
	}

	ofstream fout(OUTFILE);
	fout << k << endl;
	fout.close();
	return 0;
}
