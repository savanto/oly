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

// sorts by descending lengths
// vector size is going to be <= 200, insertion sort will do
void sort(vector<string> &v)
{
	int size = v.size();
	for (int i = 1; i < size; ++i)
		for (int j = i; j > 0; --j)
		{
			if (v[j].length() < v[j-1].length())
				break;
			string temp = v[j];
			v[j] = v[j-1];
			v[j-1] = temp;
		}
}

int prefix(const vector<string> &p, const string &s, int k)
{
	if (k >= s.length())
		return k;
	int longest = k;
	for (int i = 0; i < p.size(); ++i)
		if (p[i] == s.substr(k, p[i].length()))
		{
			int n = prefix(p, s, k + p[i].length());
			if (n > longest)
				longest = n;
		}
	return longest;
}

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

	cout << sequence.length() << endl;
//	int k = prefix(primitives, sequence, 0);




	ofstream fout(OUTFILE);
	fout << k << endl;
	fout.close();
	return 0;
}
